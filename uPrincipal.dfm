object edtHomogenea: TedtHomogenea
  Left = 0
  Top = 0
  Caption = 'Polygon Manipulation'
  ClientHeight = 582
  ClientWidth = 902
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
    Top = 509
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
  object GroupBox3: TGroupBox
    Left = 493
    Top = 234
    Width = 139
    Height = 173
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Coordenadas'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 26
    object GroupBox8: TGroupBox
      Left = 73
      Top = 20
      Width = 58
      Height = 114
      Caption = 'Eixo X'
      Color = clHighlight
      ParentBackground = False
      ParentColor = False
      TabOrder = 0
      object Max: TLabel
        Left = 16
        Top = 16
        Width = 20
        Height = 13
        Caption = 'Max'
      end
      object Min: TLabel
        Left = 16
        Top = 68
        Width = 16
        Height = 13
        Caption = 'Min'
      end
    end
  end
  object GroupBox7: TGroupBox
    Left = 502
    Top = 254
    Width = 58
    Height = 114
    Caption = 'Eixo Y'
    TabOrder = 37
    object Label4: TLabel
      Left = 20
      Top = 16
      Width = 20
      Height = 13
      Caption = 'Max'
    end
    object Label5: TLabel
      Left = 20
      Top = 68
      Width = 16
      Height = 13
      BiDiMode = bdRightToLeft
      Caption = 'Min'
      ParentBiDiMode = False
    end
  end
  object GroupBox6: TGroupBox
    Left = 801
    Top = 235
    Width = 88
    Height = 104
    Caption = 'Reflex'#227'o'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 31
  end
  object GroupBox5: TGroupBox
    Left = 493
    Top = 25
    Width = 395
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
      Left = 105
      Top = 12
      Width = 45
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Poligonos'
    end
    object btnClipping: TButton
      Left = 196
      Top = 62
      Width = 82
      Height = 24
      Caption = 'Clipping'
      TabOrder = 0
      OnClick = btnClippingClick
    end
    object Circulo: TButton
      Left = 296
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Circulo'
      TabOrder = 1
      OnClick = CirculoClick
    end
    object edRaio: TEdit
      Left = 296
      Top = 63
      Width = 73
      Height = 21
      TabOrder = 2
      Text = '0'
    end
  end
  object GroupBox4: TGroupBox
    Left = 620
    Top = 130
    Width = 269
    Height = 100
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Transformar'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 27
  end
  object btnCreatePolygon: TButton
    Left = 688
    Top = 58
    Width = 80
    Height = 24
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Poligono'
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
      ExplicitLeft = 2
      ExplicitTop = 2
    end
  end
  object lbPontos: TListBox
    Left = 503
    Top = 50
    Width = 88
    Height = 65
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    ItemHeight = 13
    TabOrder = 2
  end
  object lbPoligonos: TListBox
    Left = 596
    Top = 50
    Width = 88
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
    Left = 576
    Top = 334
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
    Left = 576
    Top = 286
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
    Left = 513
    Top = 286
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
    Left = 513
    Top = 373
    Width = 85
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
    Left = 493
    Top = 130
    Width = 123
    Height = 100
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
  object btRotacionar: TButton
    Left = 737
    Top = 198
    Width = 66
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Rotacionar'
    TabOrder = 16
    OnClick = btRotacionarClick
  end
  object edtAngulo: TEdit
    Left = 629
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
    Left = 631
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
    Left = 681
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
    Left = 737
    Top = 144
    Width = 66
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
    Left = 737
    Top = 171
    Width = 66
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
    Left = 681
    Top = 174
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
    Left = 631
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
    Left = 636
    Top = 344
    Width = 135
    Height = 80
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = 'Mover Mapa'
    Color = clMenuHighlight
    ParentBackground = False
    ParentColor = False
    TabOrder = 24
  end
  object btnLeft: TButton
    Left = 644
    Top = 375
    Width = 40
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = #9668
    TabOrder = 10
    OnClick = btnLeftClick
  end
  object btnUp: TButton
    Left = 683
    Top = 366
    Width = 40
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = #9650
    TabOrder = 9
    OnClick = btnUpClick
  end
  object btnDown: TButton
    Left = 683
    Top = 388
    Width = 40
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = #9660
    TabOrder = 12
    OnClick = btnDownClick
  end
  object btnRigth: TButton
    Left = 723
    Top = 375
    Width = 40
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = #9658
    TabOrder = 11
    OnClick = btnRigthClick
  end
  object GroupBox2: TGroupBox
    Left = 775
    Top = 344
    Width = 61
    Height = 80
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
    Left = 784
    Top = 360
    Width = 43
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '+'
    TabOrder = 13
    OnClick = btnZoomMaisClick
  end
  object btnZoomMenos: TButton
    Left = 784
    Top = 389
    Width = 43
    Height = 25
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Caption = '-'
    TabOrder = 14
    OnClick = btnZoomMenosClick
  end
  object edYWMin: TEdit
    Left = 513
    Top = 334
    Width = 34
    Height = 21
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    TabOrder = 5
    Text = '-250'
  end
  object btnRefleteV: TButton
    Left = 814
    Top = 255
    Width = 59
    Height = 34
    Caption = #8616
    TabOrder = 29
    OnClick = btnRefleteVClick
  end
  object btnRefleteH: TButton
    Left = 814
    Top = 295
    Width = 59
    Height = 32
    Caption = #8596
    TabOrder = 30
    OnClick = btnRefleteHClick
  end
  object btnRotacionarHomo: TButton
    Left = 808
    Top = 199
    Width = 66
    Height = 21
    Caption = 'Rot Homo'
    TabOrder = 32
    OnClick = btnRotacionarHomoClick
  end
  object rgCurvas: TRadioGroup
    Left = 637
    Top = 235
    Width = 158
    Height = 104
    Caption = 'Curvas'
    Color = clMenuHighlight
    Items.Strings = (
      'Castejau'
      'Bezier'
      'Hermite'
      'B-Spline'
      'Forward')
    ParentBackground = False
    ParentColor = False
    TabOrder = 33
  end
  object btnCriarCurvas: TButton
    Left = 713
    Top = 278
    Width = 75
    Height = 25
    Caption = 'Criar Curvas'
    TabOrder = 34
    OnClick = btnCriarCurvasClick
  end
  object btnTransladarHomo: TButton
    Left = 808
    Top = 145
    Width = 66
    Height = 21
    Caption = 'Trans Homo'
    TabOrder = 35
    OnClick = btnTransladarHomoClick
  end
  object btnEscalonarHomo: TButton
    Left = 808
    Top = 172
    Width = 66
    Height = 21
    Caption = 'Escal Homo'
    TabOrder = 36
    OnClick = btnEscalonarHomoClick
  end
end
