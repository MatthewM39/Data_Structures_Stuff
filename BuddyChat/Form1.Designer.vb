<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.BuddyIPBox = New System.Windows.Forms.TextBox()
        Me.Conversation_ListBox = New System.Windows.Forms.ListBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.ISay_Box = New System.Windows.Forms.TextBox()
        Me.Send_Button = New System.Windows.Forms.Button()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.BuddyPort = New System.Windows.Forms.TextBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.ListenPortBox = New System.Windows.Forms.TextBox()
        Me.Set_Button = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(13, 13)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(101, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Buddy's IP Address:"
        '
        'BuddyIPBox
        '
        Me.BuddyIPBox.Location = New System.Drawing.Point(121, 13)
        Me.BuddyIPBox.Name = "BuddyIPBox"
        Me.BuddyIPBox.Size = New System.Drawing.Size(129, 20)
        Me.BuddyIPBox.TabIndex = 1
        '
        'Conversation_ListBox
        '
        Me.Conversation_ListBox.FormattingEnabled = True
        Me.Conversation_ListBox.Location = New System.Drawing.Point(12, 117)
        Me.Conversation_ListBox.Name = "Conversation_ListBox"
        Me.Conversation_ListBox.Size = New System.Drawing.Size(238, 160)
        Me.Conversation_ListBox.TabIndex = 2
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(13, 92)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 13)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "Conversation:"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(12, 286)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(32, 13)
        Me.Label3.TabIndex = 4
        Me.Label3.Text = "I say:"
        '
        'ISay_Box
        '
        Me.ISay_Box.Location = New System.Drawing.Point(51, 286)
        Me.ISay_Box.Name = "ISay_Box"
        Me.ISay_Box.Size = New System.Drawing.Size(199, 20)
        Me.ISay_Box.TabIndex = 5
        '
        'Send_Button
        '
        Me.Send_Button.Location = New System.Drawing.Point(12, 319)
        Me.Send_Button.Name = "Send_Button"
        Me.Send_Button.Size = New System.Drawing.Size(238, 23)
        Me.Send_Button.TabIndex = 6
        Me.Send_Button.Text = "Send"
        Me.Send_Button.UseVisualStyleBackColor = True
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(45, 41)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(69, 13)
        Me.Label4.TabIndex = 7
        Me.Label4.Text = "Buddy's Port:"
        '
        'BuddyPort
        '
        Me.BuddyPort.Location = New System.Drawing.Point(121, 39)
        Me.BuddyPort.Name = "BuddyPort"
        Me.BuddyPort.Size = New System.Drawing.Size(62, 20)
        Me.BuddyPort.TabIndex = 8
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(23, 67)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(91, 13)
        Me.Label5.TabIndex = 9
        Me.Label5.Text = "My Listening Port:"
        '
        'ListenPortBox
        '
        Me.ListenPortBox.Location = New System.Drawing.Point(121, 64)
        Me.ListenPortBox.Name = "ListenPortBox"
        Me.ListenPortBox.Size = New System.Drawing.Size(62, 20)
        Me.ListenPortBox.TabIndex = 10
        '
        'Set_Button
        '
        Me.Set_Button.Location = New System.Drawing.Point(190, 67)
        Me.Set_Button.Name = "Set_Button"
        Me.Set_Button.Size = New System.Drawing.Size(60, 23)
        Me.Set_Button.TabIndex = 11
        Me.Set_Button.Text = "Set"
        Me.Set_Button.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(257, 354)
        Me.Controls.Add(Me.Set_Button)
        Me.Controls.Add(Me.ListenPortBox)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.BuddyPort)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Send_Button)
        Me.Controls.Add(Me.ISay_Box)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Conversation_ListBox)
        Me.Controls.Add(Me.BuddyIPBox)
        Me.Controls.Add(Me.Label1)
        Me.Name = "Form1"
        Me.Text = "BuddyChatV1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents BuddyIPBox As System.Windows.Forms.TextBox
    Friend WithEvents Conversation_ListBox As System.Windows.Forms.ListBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents ISay_Box As System.Windows.Forms.TextBox
    Friend WithEvents Send_Button As System.Windows.Forms.Button
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents BuddyPort As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents ListenPortBox As System.Windows.Forms.TextBox
    Friend WithEvents Set_Button As System.Windows.Forms.Button

End Class
