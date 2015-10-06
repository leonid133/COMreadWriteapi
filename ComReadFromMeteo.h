//---------------------------------------------------------------------------

#ifndef ComReadFromMeteoH
#define ComReadFromMeteoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TMemo *Memo1;
   TButton *Button1;
   TButton *Button2;
   TEdit *Edit1;
   TLabel *Label1;
   TButton *Button3;
   TLabel *Label2;
   TBevel *Bevel1;
   TCheckBox *CheckBox1;
   TTimer *Timer1;
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
   void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
