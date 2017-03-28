Imports System.Net
Imports System.Text
Imports System.Net.Sockets
Imports System.Threading

Public Class Form1
    Dim udpClient As New UdpClient
    Dim GLOIP As IPAddress
    Dim GLOINTPORT As Integer
    Dim bytCommand As Byte() = New Byte() {}

    Public receivingUdpClient As UdpClient
    Public RemoteIpEndPoint As New IPEndPoint(IPAddress.Any, 0)
    Public ThreadReceive As Thread
    Public ReceivedMessage As String
    Public Received As Boolean
    Public ListenPort As Integer
    Public run_thread As Boolean = True


    Private Sub ReceiveMessages()
        Dim receivingUdpClient As New UdpClient(ListenPort)
        Do While run_thread
            Try
                Dim receiveBytes As [Byte]() = receivingUdpClient.Receive(RemoteIpEndPoint)
                Dim returnData As String = Encoding.ASCII.GetString(receiveBytes)
                ReceivedMessage = RemoteIpEndPoint.Address.Address.ToString() + " says:" + returnData.ToString()
                Received = True
                Me.Invalidate()
            Catch e As Exception
                ReceivedMessage = e.ToString()
                Me.Invalidate()
            End Try
        Loop
    End Sub

    Private Sub Form1_Paint(ByVal sender As Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles Me.Paint
        If (Received) Then
            Received = False
            Conversation_ListBox.Items.Add(ReceivedMessage)
        End If
    End Sub

    Private Sub Send_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Send_Button.Click
        GLOIP = IPAddress.Parse(BuddyIPBox.Text)
        GLOINTPORT = BuddyPort.Text
        udpClient.Connect(GLOIP, GLOINTPORT)
        bytCommand = Encoding.ASCII.GetBytes(ISay_Box.Text)
        udpClient.Send(bytCommand, bytCommand.Length)
        Conversation_ListBox.Items.Add("I say: " + ISay_Box.Text)
        ISay_Box.Text = ""



    End Sub

    Private Sub Set_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Set_Button.Click
        If (ListenPortBox.Text <> "") Then
            ListenPort = ListenPortBox.Text
            ThreadReceive = New Thread(AddressOf ReceiveMessages)
            Received = False
            ThreadReceive.Start()
            Set_Button.Enabled = False
        Else
            Conversation_ListBox.Items.Add("Must set proper listening port!")
        End If
    End Sub
End Class
