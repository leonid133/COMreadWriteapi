//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ComReadFromMeteo.h"
#include <windows.h>
#include <vector.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------------
#define assert(ignore)((void)0)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool perekl=false;
struct hComException
{
};
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   static int TIMEOUT = 7000;
   HANDLE hCom;

   hCom = CreateFile("Com1",GENERIC_READ | GENERIC_WRITE,0,NULL, OPEN_EXISTING, 0, NULL);
   if( hCom == INVALID_HANDLE_VALUE )
   {
      ShowMessage("Com port error");
      CloseHandle(hCom);
   }
   else
   {
      SetCommMask(hCom, EV_RXCHAR);
      SetupComm(hCom, 1500, 1500);

      COMMTIMEOUTS CommTimeOuts;
      CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
      CommTimeOuts.ReadTotalTimeoutMultiplier = TIMEOUT;
      CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
      CommTimeOuts.WriteTotalTimeoutMultiplier = TIMEOUT;
      CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

      if(!SetCommTimeouts(hCom, &CommTimeOuts))
      {
         hCom = 0;
         throw hComException();
      }

      DCB dcb;

      memset(&dcb, 0, sizeof(dcb));
      dcb.DCBlength = sizeof(DCB);
      GetCommState(hCom, &dcb);
      dcb.BaudRate = CBR_57600;
      dcb.fParity = 0;
      dcb.ByteSize = 8;
      dcb.Parity = EVENPARITY;
      dcb.StopBits = ONESTOPBIT;
      dcb.fAbortOnError = FALSE;
      dcb.fDtrControl = DTR_CONTROL_DISABLE;
      dcb.fRtsControl = RTS_CONTROL_DISABLE;
      dcb.fBinary = TRUE;
      dcb.fParity = FALSE;
      dcb.fInX = FALSE;
      dcb.fOutX = FALSE;
      dcb.XonChar = 0;
      dcb.XoffChar = (unsigned char)0xFF;
      dcb.fErrorChar = FALSE;
      dcb.fNull = FALSE;
      dcb.fOutxCtsFlow = FALSE;
      dcb.fOutxDsrFlow = FALSE;
      dcb.XonLim = 128;
      dcb.XoffLim = 128;
      
      SetCommState(hCom,&dcb);
      PurgeComm(hCom, PURGE_RXCLEAR);
      DWORD begin = GetTickCount();
      DWORD feedback = 0;
      BYTE data1[50];
      vector<unsigned char> data(data1, data1+50);

      unsigned char* buf = &data[0];
      DWORD len = (DWORD)data.size();
      int attempts = 3;
      while(len && (attempts || (GetTickCount()-begin) < (DWORD)TIMEOUT/3))
      {
         if(attempts) attempts--;
         if(!ReadFile(hCom, buf, len, &feedback, NULL))
         {
            CloseHandle(hCom);
            hCom = 0;
            throw hComException();
         }
         assert(feedback <= len);
         len -= feedback;
         buf += feedback;
      }
      if(len)
      {
         CloseHandle(hCom);
         hCom = 0;
         throw hComException();
      }
      int i;
      i = 0;
      while(i<(DWORD)data.size())
      {
         //Memo1->Lines->Add(i);
         //Memo1->Lines->Add(data[i]);
         i++;
      }   

      unsigned char tmp = 0;
      for (int i = 0; i < 15; i++ )
  	     	tmp = tmp ^ data[i];

      if(data[0]==0x68 && tmp==data[15])
      {
         Memo1->Lines->Add("40---------------");

         long Lat;
         Lat = data[1]&~0x80;
         Lat |= ((long)(data[2]&~0x80)<<7);
         Lat |= ((long)(data[3]&~0x80)<<14);
         Lat |= ((long)(data[4]&~0x80)<<21);
         Memo1->Lines->Add("Lat");
         Memo1->Lines->Add(Lat);

         long Lon;
         Lon = data[5]&~0x80;
         Lon |= ((long)(data[6]&~0x80)<<7);
         Lon |= ((long)(data[7]&~0x80)<<14);
         Lon |= ((long)(data[8]&~0x80)<<21);;
         Memo1->Lines->Add("Lon");
         Memo1->Lines->Add(Lon);

         int Angle;
         Angle = data[9]&~0x80;
         Angle |= ((int)(data[10]&~0x80)<<7);
         Memo1->Lines->Add("Angle");
         Memo1->Lines->Add(Angle);

         int Vspeed;
         Vspeed = data[11]&~0x80;
         Vspeed |= ((int)(data[12]&~0x80)<<7);
         Memo1->Lines->Add("V Speed");
         Memo1->Lines->Add(Vspeed);

         int Pressure;
         Pressure = data[13]&~0x80;
         Pressure |= ((int)(data[14]&~0x80)<<7);
         Memo1->Lines->Add("Pressure");
         Memo1->Lines->Add(Pressure);
      }
      tmp = 0;
      for (int i = 0; i < 3; i++ )
	     	tmp = tmp ^ data[16+i];

      if(data[16]==0x69 && tmp == data[19])
      {
         int Antena;
         Antena = data[17]&~0x80;
         Antena |= ((int)(data[18]&~0x80)<<7);
         Memo1->Lines->Add("41---------------");
         Memo1->Lines->Add("Antena Angle");
         Memo1->Lines->Add(Antena);
      }

   }
   CloseHandle(hCom);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   int A;
   A = Edit1->Text.ToInt();

   if(A>360)
   {
      A=360;
   }
   else if(A<0)
   {
      A=0;
   }
   Edit1->Text = A;
   static int TIMEOUT = 7000;
   HANDLE hCom;

   hCom = CreateFile("Com1",GENERIC_READ | GENERIC_WRITE,0,NULL, OPEN_EXISTING, 0, NULL);
   if( hCom == INVALID_HANDLE_VALUE )
   {
      ShowMessage("Com port error");
      CloseHandle(hCom);
   }
   else
   {
      SetCommMask(hCom, EV_RXCHAR);
      SetupComm(hCom, 1500, 1500);

      COMMTIMEOUTS CommTimeOuts;
      CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
      CommTimeOuts.ReadTotalTimeoutMultiplier = TIMEOUT;
      CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
      CommTimeOuts.WriteTotalTimeoutMultiplier = TIMEOUT;
      CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

      if(!SetCommTimeouts(hCom, &CommTimeOuts))
      {
         hCom = 0;
         throw hComException();
      }

      DCB dcb;

      memset(&dcb, 0, sizeof(dcb));
      dcb.DCBlength = sizeof(DCB);
      GetCommState(hCom, &dcb);
      dcb.BaudRate = CBR_57600;
      dcb.fParity = 0;
      dcb.ByteSize = 8;
      dcb.Parity = EVENPARITY;
      dcb.StopBits = ONESTOPBIT;
      dcb.fAbortOnError = FALSE;
      dcb.fDtrControl = DTR_CONTROL_DISABLE;
      dcb.fRtsControl = RTS_CONTROL_DISABLE;
      dcb.fBinary = TRUE;
      dcb.fParity = FALSE;
      dcb.fInX = FALSE;
      dcb.fOutX = FALSE;
      dcb.XonChar = 0;
      dcb.XoffChar = (unsigned char)0xFF;
      dcb.fErrorChar = FALSE;
      dcb.fNull = FALSE;
      dcb.fOutxCtsFlow = FALSE;
      dcb.fOutxDsrFlow = FALSE;
      dcb.XonLim = 128;
      dcb.XoffLim = 128;
      
      SetCommState(hCom,&dcb);
      PurgeComm(hCom, PURGE_RXCLEAR);
      DWORD begin = GetTickCount();
      DWORD feedback = 0;
      BYTE data1[4];
      vector<unsigned char> data(data1, data1+4);

      unsigned char* buf = &data[0];
      DWORD len = (DWORD)data.size();
      data[0] = 46;
		data[0] &= ~0x80;
		data[0] |= 0x40; //кодовый байт
      data[1] = (A & 0x007f)| 0x80;
      data[2] = ((A & 0x3f80) >> 7)| 0x80;
      data[3] = 0;
      for (int i = 0; i < 3; i++ )
		  	data[3] = data[3] ^ data[i];

      int attempts = 3;
      while(len && (attempts || (GetTickCount()-begin) < (DWORD)TIMEOUT/3))
      {
         if(attempts) attempts--;
         if(!WriteFile(hCom, buf, len, &feedback, NULL))
         {
            CloseHandle(hCom);
            hCom = 0;
            throw hComException();
         }
         assert(feedback <= len);
         len -= feedback;
         buf += feedback;
      }
      if(len)
      {
         CloseHandle(hCom);
         hCom = 0;
         throw hComException();
      }
   }
   CloseHandle(hCom);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
  String txt;
   Set <char, '0', '9'> Dig;
	Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' <<'7'<<'8'<< '9';

   if(Key == 8)
   {

   }
   else if(Key == 0x2e)
	{
      Key = 0;
   }
	else if(Key == 0x2c)
	{
   	Key = 0x2e;
      Key = 0;
   }
   else if(Key == 13)
   {
   }
   else if(Key == 45)
   {
   }
   else if(Key == 16)
   {
   }
	else if ( !Dig.Contains(Key) )
	{
		Key = 0;
		Beep();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    Button1Click(Sender);
    /*
    if(perekl==false)
    {
      perekl=true;
      Button1Click(Sender);
    }
    else
    {
      perekl=false;
      Button2Click(Sender);
    }  */
}
//---------------------------------------------------------------------------

