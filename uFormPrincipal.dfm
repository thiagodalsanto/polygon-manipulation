object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Projeto CG'
  ClientHeight = 540
  ClientWidth = 842
  Color = clHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbVp: TLabel
    Left = 445
    Top = 510
    Width = 24
    Height = 13
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '(0,0)'
  end
  object lbMundo: TLabel
    Left = 7
    Top = 510
    Width = 24
    Height = 13
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '(0,0)'
  end
  object Label3: TLabel
    Left = 496
    Top = 283
    Width = 3
    Height = 13
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
  end
  object GroupBox5: TGroupBox
    Left = 496
    Top = 23
    Width = 339
    Height = 101
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Criar Poligono'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 28
    object Pontos: TLabel
      Left = 12
      Top = 12
      Width = 33
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Pontos'
    end
    object Poligonos: TLabel
      Left = 118
      Top = 12
      Width = 45
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Poligonos'
    end
  end
  object GroupBox4: TGroupBox
    Left = 642
    Top = 130
    Width = 193
    Height = 100
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Estados de Poligono'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 27
  end
  object GroupBox3: TGroupBox
    Left = 494
    Top = 266
    Width = 142
    Height = 160
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Mudar Mundo'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 26
    object Label1: TLabel
      Left = 85
      Top = 23
      Width = 32
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'xWMin'
    end
    object Label2: TLabel
      Left = 17
      Top = 23
      Width = 32
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'yWMin'
    end
    object Label5: TLabel
      Left = 84
      Top = 67
      Width = 36
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'xWMax'
    end
    object Label4: TLabel
      Left = 17
      Top = 67
      Width = 36
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'xWMax'
    end
  end
  object btnCreatePolygon: TButton
    Left = 734
    Top = 72
    Width = 80
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Novo Poligono'
    TabOrder = 0
    OnClick = btnCreatePolygonClick
  end
  object Panel1: TPanel
    Left = 7
    Top = 23
    Width = 483
    Height = 482
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 1
    object Image1: TImage
      Left = 1
      Top = 1
      Width = 481
      Height = 480
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alClient
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      ExplicitWidth = 480
    end
  end
  object lbPontos: TListBox
    Left = 503
    Top = 50
    Width = 96
    Height = 65
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    ItemHeight = 13
    TabOrder = 2
  end
  object lbPoligonos: TListBox
    Left = 607
    Top = 50
    Width = 96
    Height = 65
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    ItemHeight = 13
    TabOrder = 3
    OnMouseDown = lbPoligonosMouseDown
  end
  object edXWMin: TEdit
    Left = 578
    Top = 308
    Width = 34
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 4
    Text = '-250'
  end
  object edXWMax: TEdit
    Left = 511
    Top = 308
    Width = 34
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 6
    Text = '250'
  end
  object edYWMax: TEdit
    Left = 511
    Top = 353
    Width = 34
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 7
    Text = '250'
  end
  object btnUpdate: TButton
    Left = 516
    Top = 389
    Width = 95
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Atualizar Mundo'
    TabOrder = 8
    OnClick = btnUpdateClick
  end
  object rgTipoReta: TRadioGroup
    Left = 494
    Top = 130
    Width = 142
    Height = 132
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Tipos de Reta'
    Color = clMenuHighlight
    ItemIndex = 0
    Items.Strings = (
      'Move To/ Line To'
      'DDA'
      'Bresenham')
    ParentBackground = False
    ParentColor = False
    TabOrder = 15
    OnClick = rgTipoRetaClick
  end
  object btnRotation: TButton
    Left = 752
    Top = 197
    Width = 72
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Rotacionar'
    TabOrder = 16
    OnClick = btnRotationClick
  end
  object edtAngulo: TEdit
    Left = 650
    Top = 199
    Width = 96
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 17
    Text = '0'
  end
  object edTransladarX: TEdit
    Left = 650
    Top = 148
    Width = 46
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 18
    Text = '0'
  end
  object edTransladarY: TEdit
    Left = 702
    Top = 148
    Width = 44
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 19
    Text = '0'
  end
  object btTransladar: TButton
    Left = 752
    Top = 146
    Width = 72
    Height = 23
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Transladar'
    TabOrder = 20
    OnClick = btTransladarClick
  end
  object btEscalonar: TButton
    Left = 752
    Top = 170
    Width = 72
    Height = 23
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Escalonar'
    TabOrder = 21
    OnClick = btEscalonarClick
  end
  object edEscalonarY: TEdit
    Left = 702
    Top = 173
    Width = 44
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 22
    Text = '1'
  end
  object edEscalonarX: TEdit
    Left = 650
    Top = 173
    Width = 46
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 23
    Text = '1'
  end
  object GroupBox1: TGroupBox
    Left = 642
    Top = 236
    Width = 193
    Height = 111
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Comandos'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 24
  end
  object btnLeft: TButton
    Left = 660
    Top = 278
    Width = 43
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Left'
    TabOrder = 10
    OnClick = btnLeftClick
  end
  object btnUp: TButton
    Left = 715
    Top = 252
    Width = 43
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Up'
    TabOrder = 9
    OnClick = btnUpClick
  end
  object btnDown: TButton
    Left = 715
    Top = 305
    Width = 43
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Down'
    TabOrder = 12
    OnClick = btnDownClick
  end
  object btnRigth: TButton
    Left = 770
    Top = 278
    Width = 44
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Rigth'
    TabOrder = 11
    OnClick = btnRigthClick
  end
  object GroupBox2: TGroupBox
    Left = 642
    Top = 353
    Width = 193
    Height = 73
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Zoom'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 25
  end
  object btnZoomMais: TButton
    Left = 667
    Top = 372
    Width = 59
    Height = 38
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '+ Zoom'
    TabOrder = 13
    OnClick = btnZoomMaisClick
  end
  object btnZoomMenos: TButton
    Left = 752
    Top = 372
    Width = 59
    Height = 38
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '- Zoom'
    TabOrder = 14
    OnClick = btnZoomMenosClick
  end
  object edYWMin: TEdit
    Left = 577
    Top = 353
    Width = 34
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 5
    Text = '-250'
  end
end
