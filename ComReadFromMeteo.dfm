object Form1: TForm1
  Left = 443
  Top = 147
  Width = 514
  Height = 451
  Caption = #1054#1090#1083#1072#1076#1082#1072' '#1084#1077#1090#1077#1086#1089#1090#1072#1085#1094#1080' Com1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 8
    Top = 72
    Width = 141
    Height = 16
    Caption = #1062#1077#1083#1077#1074#1086#1081' '#1091#1075#1086#1083' '#1072#1085#1090#1077#1085#1099
  end
  object Label2: TLabel
    Left = 208
    Top = 64
    Width = 189
    Height = 16
    Caption = #1058#1077#1083#1077#1084#1077#1090#1088#1080#1103' '#1089' '#1052#1077#1090#1077#1086#1089#1090#1072#1085#1094#1080#1080
  end
  object Bevel1: TBevel
    Left = 0
    Top = 128
    Width = 185
    Height = 18
    Shape = bsBottomLine
  end
  object Memo1: TMemo
    Left = 208
    Top = 88
    Width = 265
    Height = 289
    Lines.Strings = (
      '')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TButton
    Left = 216
    Top = 16
    Width = 85
    Height = 30
    Caption = #1055#1088#1080#1077#1084
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 16
    Width = 85
    Height = 30
    Caption = #1055#1077#1088#1077#1076#1072#1095#1072
    TabOrder = 2
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 104
    Width = 121
    Height = 24
    TabOrder = 3
    Text = '0'
    OnKeyPress = Edit1KeyPress
  end
  object Button3: TButton
    Left = 8
    Top = 160
    Width = 85
    Height = 30
    Caption = #1055#1077#1088#1077#1076#1072#1095#1072
    TabOrder = 4
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 208
    Width = 97
    Height = 17
    Caption = #1042#1082#1083' / '#1042#1099#1082#1083
    TabOrder = 5
  end
  object Timer1: TTimer
    Interval = 7000
    OnTimer = Timer1Timer
    Left = 456
    Top = 8
  end
end
