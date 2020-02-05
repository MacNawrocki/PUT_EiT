#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<atlbase.h>
#include"res.h"
#include"OpenFileDialog.h"
#include"AudioFile.h"
#include"Commctrl.h"
#include <dshow.h>
using namespace std;

#define X_MIN 15
#define X_MAX 250
#define Y_MIN 140
#define Y_MAX 170
#define X_WIDTH 75
#define X_GAP 5
#define Y_WIDTH 30
#define COLOR_NEUTRAL RGB(200,200,200)
#define COLOR_OUTLINE RGB(0,0,0)
#define COLOR_RED RGB(250,0,0)
#define COLOR_PINK RGB(250,150,150)

void DrawPlay(HDC hdc, int color);
void DrawPause(HDC hdc, int color);
void DrawStop(HDC hdc, int color);

void ClickPlay(HWND hwndDlg);
void ClickPause(HWND hwndDlg);
void ClickStop(HWND hwndDlg);

void ChangeStatus(int id, HWND hwndDlg);
void ChangeTime(HWND hwndDlg);
void MoveSliderPosition(HWND hwndDlg);

AudioFile* CurrentAudioFile = new AudioFile;
const WORD ID_TIMER = 1;
bool isMoving=TRUE;
SCROLLINFO info;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case (BN_CLICKED) :
      switch (LOWORD(wParam))
      {
      case IDC_BUTTONOPEN:
      {
        OpenFileDialog* openFileDialog1 = new OpenFileDialog();
        openFileDialog1->Title = "Open Audio File";
        openFileDialog1->Filter = "All Files|*.*";
        if (openFileDialog1->ShowDialog())
        {
          LPCSTR sFileName = openFileDialog1->FileName;
          USES_CONVERSION;
          LPCWSTR wFileName = A2W(sFileName);
          CurrentAudioFile->Load(wFileName);
          HWND hwndTextName = GetDlgItem(hwndDlg, IDC_EDITNAME);
          SetWindowText(hwndTextName, sFileName);
          KillTimer(hwndDlg, ID_TIMER);
          ChangeTime(hwndDlg);
          MoveSliderPosition(hwndDlg);
          if (CurrentAudioFile->isReady) ChangeStatus(1, hwndDlg);
          else ChangeStatus(2, hwndDlg);
        }
        return TRUE;
      }
      }
    }
  return FALSE;

  case WM_LBUTTONDOWN:
  {
	  HDC hdc = GetDC(hwndDlg);
		  int x = LOWORD(lParam);
		  int y = HIWORD(lParam);
		  if ((x > X_MIN && x < X_MAX) && ((y > Y_MIN) && (y < Y_MAX)))
		  {
			  if (x > X_MIN && x < X_MIN + X_WIDTH) ClickPlay(hwndDlg);
			  if (x > X_MIN + (X_WIDTH + X_GAP) && x < X_MIN + X_WIDTH + (X_WIDTH + X_GAP)) ClickPause(hwndDlg);
			  if (x > X_MIN + X_MAX-X_WIDTH && x < X_MAX) ClickStop(hwndDlg);
		  }
	  ReleaseDC(hwndDlg, hdc);
  }
  return FALSE;

  case WM_PAINT:
  {
	  HDC hdc = GetDC(hwndDlg);
	  DrawPlay(hdc,0);
	  DrawPause(hdc,0);
	  DrawStop(hdc,0);
	  ReleaseDC(hwndDlg, hdc);
	  return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
  }
  return FALSE;

  case WM_HSCROLL:
  {
    HWND hwndScrollBar = (HWND)lParam;
    if (hwndScrollBar == GetDlgItem(hwndDlg, IDC_SLIDERPROG))
    {
      __int64 iPosNew = (__int64)SendMessage(hwndScrollBar, TBM_GETPOS, 0, 0) * 100;
      //Chwycenie i przesuniêcie suwaka:
      isMoving = FALSE;
      if (LOWORD(wParam) == SB_THUMBPOSITION)
      {
        SetTimer(hwndDlg, ID_TIMER, 100, NULL);
        CurrentAudioFile->SetPositions(&iPosNew, &iPosNew, FALSE);
        MoveSliderPosition(hwndDlg);
        return TRUE;
      }
    }
    
    if (hwndScrollBar == GetDlgItem(hwndDlg, IDC_SLIDERVOL))
    {
      if (LOWORD(wParam) == SB_THUMBPOSITION)
      {
        long aNewVol = SendMessage(hwndScrollBar, TBM_GETPOS, 0, 0);
        CurrentAudioFile->SetVolume(aNewVol);
        SendMessage(hwndScrollBar, TBM_SETPOS, TRUE, aNewVol);
        return TRUE;
      }
    }
  }
  return FALSE;

  case WM_TIMER:
    {
      if (isMoving) MoveSliderPosition(hwndDlg);
      ChangeTime(hwndDlg);
      return TRUE;
    }
  return FALSE;

  case WM_CLOSE:
    {
      KillTimer(hwndDlg, ID_TIMER);
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      return TRUE;
    }
  return FALSE;
  
  }
  return FALSE;
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
  }
  return 0;
}

void ChangeStatus(int id, HWND hwndDlg)
{
  HWND hwndStatus = GetDlgItem(hwndDlg, IDC_STATUS);
  CHAR szText[500];
  HDC hdc = GetDC(hwndDlg);
  DrawPlay(hdc, 0);
  DrawPause(hdc, 0);
  DrawStop(hdc, 0);
  ReleaseDC(hwndDlg, hdc);
  switch (id)
  {
  case 0: {sprintf_s(szText, "No file opened."); SetWindowText(hwndStatus, szText); return;}
  case 1: {sprintf_s(szText, "Correct file loaded."); SetWindowText(hwndStatus, szText); return;}
  case 2: {sprintf_s(szText, "Incorrect file loaded!"); SetWindowText(hwndStatus, szText); return;}
  case 3: {sprintf_s(szText, "File playing."); SetWindowText(hwndStatus, szText); HDC hdc = GetDC(hwndDlg);  DrawPlay(hdc, 1);  ReleaseDC(hwndDlg, hdc); return;}
  case 4: {sprintf_s(szText, "File paused."); SetWindowText(hwndStatus, szText); HDC hdc = GetDC(hwndDlg);  DrawPause(hdc, 1);  ReleaseDC(hwndDlg, hdc); return;}
  case 5: {sprintf_s(szText, "Stopped playing file."); SetWindowText(hwndStatus, szText); HDC hdc = GetDC(hwndDlg);  DrawStop(hdc, 1);  ReleaseDC(hwndDlg, hdc); return;}
  case 6: {sprintf_s(szText, "Finished playing file."); SetWindowText(hwndStatus, szText); return;}
  }
  return;
}

void ChangeTime(HWND hwndDlg)
{
  CHAR szText[500];
  int audioCurrentPositionMin = (CurrentAudioFile->GetCurrentPosition() / 100000) / 60;
  int audioCurrentPositionSec = (CurrentAudioFile->GetCurrentPosition() / 100000) % 60;
  int audioDurationMin = (CurrentAudioFile->audioDuration / 100000) / 60;
  int audioDurationSec = (CurrentAudioFile->audioDuration / 100000) % 60;
  sprintf_s(szText, "%d:%d/%d:%d",
    audioCurrentPositionMin,
    audioCurrentPositionSec,
    audioDurationMin,
    audioDurationSec);
  HWND hwndDuration = GetDlgItem(hwndDlg, IDC_TIME);
  SetWindowText(hwndDuration, szText);
  if (CurrentAudioFile->isPlaying & (CurrentAudioFile->GetCurrentPosition() == CurrentAudioFile->audioDuration)) ChangeStatus(6, hwndDlg);
}

void MoveSliderPosition(HWND hwndDlg) 
{
  HWND hwndSlider = GetDlgItem(hwndDlg, IDC_SLIDERPROG);
  LPARAM aDuration = CurrentAudioFile->audioDuration;
  LPARAM aPosition = CurrentAudioFile->GetCurrentPosition();
  SendMessage(hwndSlider, TBM_SETRANGEMAX,FALSE, aDuration);
  SendMessage(hwndSlider, TBM_SETPOS, TRUE, aPosition);
  if(!isMoving) isMoving = TRUE;
}

void DrawPlay(HDC hdc, int color)
{
	HPEN hPenOutline = CreatePen(PS_SOLID, 2, COLOR_OUTLINE);
	HPEN hPenOutlineRed = CreatePen(PS_SOLID, 2, COLOR_RED);
	HBRUSH hBrushInside = CreateSolidBrush(COLOR_NEUTRAL);
	HBRUSH hBrushInsidePink = CreateSolidBrush(COLOR_PINK);
	if (color == 1) { SelectObject(hdc, hPenOutlineRed); SelectObject(hdc, hBrushInsidePink);}
	else { SelectObject(hdc, hPenOutline); SelectObject(hdc, hBrushInside);}
	Rectangle(hdc, X_MIN, Y_MIN, X_MIN + X_WIDTH, Y_MAX);
	DeleteObject(hBrushInside);
	DeleteObject(hPenOutline);
	DeleteObject(hBrushInsidePink);
	DeleteObject(hPenOutlineRed);

	HPEN hPenSymbol = CreatePen(PS_SOLID, 5, COLOR_OUTLINE);
	HPEN hPenSymbolRed = CreatePen(PS_SOLID, 5, COLOR_RED);
	if (color == 1) { SelectObject(hdc, hPenSymbolRed);}
	else { SelectObject(hdc, hPenSymbol);}
	MoveToEx(hdc, X_MIN + 30, Y_MIN + 10, nullptr);
	LineTo(hdc, X_MIN + 30, Y_MIN + 20);
	LineTo(hdc, X_MIN + 40, Y_MIN + 15);
	MoveToEx(hdc, X_MIN + 40, Y_MIN + 15, nullptr);
	LineTo(hdc, X_MIN + 30, Y_MIN + 10);
	LineTo(hdc, X_MIN + 35, Y_MIN + 15);
	DeleteObject(hPenSymbol);
	DeleteObject(hPenSymbolRed);
}

void DrawPause(HDC hdc, int color)
{
	HPEN hPenOutline = CreatePen(PS_SOLID, 2, COLOR_OUTLINE);
	HPEN hPenOutlineRed = CreatePen(PS_SOLID, 2, COLOR_RED);
	HBRUSH hBrushInside = CreateSolidBrush(COLOR_NEUTRAL);
	HBRUSH hBrushInsidePink = CreateSolidBrush(COLOR_PINK);
	if (color == 1) { SelectObject(hdc, hPenOutlineRed); SelectObject(hdc, hBrushInsidePink); }
	else { SelectObject(hdc, hPenOutline); SelectObject(hdc, hBrushInside); }
	Rectangle(hdc, X_MIN + (X_WIDTH + X_GAP), Y_MIN, X_MIN + X_WIDTH + (X_WIDTH + X_GAP), Y_MAX);
	DeleteObject(hBrushInside);
	DeleteObject(hPenOutline);
	DeleteObject(hBrushInsidePink);
	DeleteObject(hPenOutlineRed);

	HPEN hPenSymbol = CreatePen(PS_SOLID, 5, COLOR_OUTLINE);
	HPEN hPenSymbolRed = CreatePen(PS_SOLID, 5, COLOR_RED);
	if (color == 1) { SelectObject(hdc, hPenSymbolRed); }
	else { SelectObject(hdc, hPenSymbol); }
	MoveToEx(hdc, X_MIN + (X_WIDTH + X_GAP) + 30, Y_MIN + 10, nullptr);
	LineTo(hdc, X_MIN + (X_WIDTH + X_GAP) + 30, Y_MIN + 20);
	MoveToEx(hdc, X_MIN + (X_WIDTH + X_GAP) + 37, Y_MIN + 10, nullptr);
	LineTo(hdc, X_MIN + (X_WIDTH + X_GAP) + 37, Y_MIN + 20);
	DeleteObject(hPenSymbol);
	DeleteObject(hPenSymbolRed);
}

void DrawStop(HDC hdc, int color)
{
	HPEN hPenOutline = CreatePen(PS_SOLID, 2, COLOR_OUTLINE);
	HPEN hPenOutlineRed = CreatePen(PS_SOLID, 2, COLOR_RED);
	HBRUSH hBrushInside = CreateSolidBrush(COLOR_NEUTRAL);
	HBRUSH hBrushInsidePink = CreateSolidBrush(COLOR_PINK);
	if (color == 1) { SelectObject(hdc, hPenOutlineRed); SelectObject(hdc, hBrushInsidePink); }
	else { SelectObject(hdc, hPenOutline); SelectObject(hdc, hBrushInside); }
	Rectangle(hdc, X_MIN + (X_WIDTH + X_GAP)*2, Y_MIN, X_MAX, Y_MAX);
	DeleteObject(hBrushInside);
	DeleteObject(hPenOutline);
	DeleteObject(hBrushInsidePink);
	DeleteObject(hPenOutlineRed);

	HPEN hPenSymbol = CreatePen(PS_SOLID, 5, COLOR_OUTLINE);
	HPEN hPenSymbolRed = CreatePen(PS_SOLID, 5, COLOR_RED);
	HBRUSH hBrushSymbol = CreateSolidBrush(COLOR_OUTLINE);
	HBRUSH hBrushSymbolRed = CreateSolidBrush(COLOR_RED);
	if (color == 1) { SelectObject(hdc, hPenSymbolRed); SelectObject(hdc, hBrushSymbolRed);}
	else { SelectObject(hdc, hPenSymbol); SelectObject(hdc, hBrushSymbol);}
	Rectangle(hdc, X_MAX - 45, Y_MIN + 10, X_MAX-35, Y_MIN + 20);
	DeleteObject(hBrushSymbol);
	DeleteObject(hPenSymbol);
	DeleteObject(hBrushSymbolRed);
	DeleteObject(hPenSymbolRed);
}

void ClickPlay(HWND hwndDlg)
{
	CurrentAudioFile->Play();
	if (CurrentAudioFile->isPlaying) ChangeStatus(3, hwndDlg);
	SetTimer(hwndDlg, ID_TIMER, 100, NULL);
	long aMaxVol = CurrentAudioFile->GetVolume();
	//char szText[200];
	//wsprintf(szText, "Vol tego pliku: %d",aMaxVol);
	//MessageBox(hwndDlg, szText, TEXT("VOL"), MB_OK);
	HWND hwndVolume = GetDlgItem(hwndDlg, IDC_SLIDERVOL);
	SendMessage(hwndVolume, TBM_SETRANGEMAX, FALSE, aMaxVol);
	SendMessage(hwndVolume, TBM_SETPOS, TRUE, SendMessage(hwndVolume, TBM_GETRANGEMAX, 0, 0));
}

void ClickPause(HWND hwndDlg)
{
	CurrentAudioFile->Pause();
	if (CurrentAudioFile->isReady) ChangeStatus(4, hwndDlg);
}

void ClickStop(HWND hwndDlg)
{
	CurrentAudioFile->Stop();
	ChangeStatus(5, hwndDlg);
	CurrentAudioFile->Cleanup();
	KillTimer(hwndDlg, ID_TIMER);
	ChangeTime(hwndDlg);
	MoveSliderPosition(hwndDlg);
	HWND hwndTextName = GetDlgItem(hwndDlg, IDC_EDITNAME);
	SetWindowText(hwndTextName, "");
}