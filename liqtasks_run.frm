VERSION 5.00
Begin VB.Form liqtasks_run 
   BackColor       =   &H00000000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Base Form"
   ClientHeight    =   7200
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   12015
   BeginProperty Font 
      Name            =   "Trebuchet MS"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "frmBase800x480"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7200
   ScaleWidth      =   12015
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox backplane 
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      Height          =   6405
      Left            =   0
      ScaleHeight     =   6405
      ScaleWidth      =   12015
      TabIndex        =   3
      Top             =   0
      Width           =   12015
      Begin VB.PictureBox Picture1 
         BackColor       =   &H00404040&
         BorderStyle     =   0  'None
         Height          =   2655
         Left            =   0
         ScaleHeight     =   2655
         ScaleWidth      =   12015
         TabIndex        =   6
         Top             =   2790
         Width           =   12015
         Begin VB.Label Label2 
            BackColor       =   &H00404000&
            Caption         =   "Completed items"
            BeginProperty Font 
               Name            =   "Trebuchet MS"
               Size            =   20.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FFFFFF&
            Height          =   615
            Left            =   0
            TabIndex        =   7
            Top             =   0
            Width           =   12015
         End
      End
      Begin VB.PictureBox bodytodo 
         BackColor       =   &H00404040&
         BorderStyle     =   0  'None
         Height          =   2655
         Left            =   0
         ScaleHeight     =   2655
         ScaleWidth      =   12015
         TabIndex        =   4
         Top             =   0
         Width           =   12015
         Begin VB.Label Label1 
            BackColor       =   &H00004000&
            Caption         =   "Todo items"
            BeginProperty Font 
               Name            =   "Trebuchet MS"
               Size            =   20.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FFFFFF&
            Height          =   615
            Left            =   0
            TabIndex        =   5
            Top             =   0
            Width           =   12015
         End
      End
   End
   Begin VB.Label cmdremove 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Remove"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   7890
      TabIndex        =   2
      Top             =   6480
      Width           =   1935
   End
   Begin VB.Label cmdcomplete 
      Alignment       =   2  'Center
      BackColor       =   &H00404000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Complete"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   5070
      TabIndex        =   1
      Top             =   6480
      Width           =   2745
   End
   Begin VB.Label cmdnew 
      Alignment       =   2  'Center
      BackColor       =   &H00004000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "New"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   735
      Left            =   9930
      TabIndex        =   0
      Top             =   6480
      Width           =   2085
   End
End
Attribute VB_Name = "liqtasks_run"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdall_Click()

End Sub
