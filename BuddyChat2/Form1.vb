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

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        GLOIP = IPAddress.Parse(BuddyIPBox.Text)
        GLOINTPORT = BuddyPort.Text
        udpClient.Connect(GLOIP, GLOINTPORT)
        bytCommand = Encoding.ASCII.GetBytes(ISay_Box.Text)
        udpClient.Send(bytCommand, bytCommand.Length)
        Conversation_ListBox.Items.Add("I say: " + ISay_Box.Text)
        ISay_Box.Text = ""
    End Sub

    Private Sub ReceiveMessages()
        Dim receivingUdpClient As New UdpClient(ListenPort)
        Do While run_thread
            Try
                Dim receiveBytes As [Byte]() = receivingUdpClient.Receive(RemoteIpEndPoint)
                Dim returnData As String = Encoding.ASCII.GetString(receiveBytes)
                ReceivedMessage = RemoteIpEndPoint.Address.Address.ToString() + " says:" + returnData.ToString()
                Dim myString As String = returnData.ToString()
                myString = myString.ToLower() ' make it all lowercase before comparing it
                Dim flag As Boolean
                flag = True
                Dim returnWord As String
                returnWord = "PANDA"
                If myString = "monkey" Then
                    returnWord = "Banana"
                    flag = False
                ElseIf myString = "elephant" Then
                    returnWord = "Mouse"
                    flag = False
                ElseIf myString = "flower" Then
                    returnWord = "Beautiful"
                    flag = False
                ElseIf myString = "house" Then
                    returnWord = "Safe"
                    flag = False
                ElseIf myString = "car" Then
                    returnWord = "Fast"
                    flag = False
                End If
                If flag = False Then
                    GLOIP = IPAddress.Parse(BuddyIPBox.Text)
                    GLOINTPORT = BuddyPort.Text
                    udpClient.Connect(GLOIP, GLOINTPORT)
                    bytCommand = Encoding.ASCII.GetBytes(returnWord)
                    udpClient.Send(bytCommand, bytCommand.Length)
                    Conversation_ListBox.Items.Add("I say: " + returnWord)
                    flag = True
                End If
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

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        If (ListenPortBox.Text <> "") Then
            ListenPort = ListenPortBox.Text
            ThreadReceive = New Thread(AddressOf ReceiveMessages)
            Received = False
            ThreadReceive.Start()
            Button2.Enabled = False
        Else
            Conversation_ListBox.Items.Add("Must set proper listening port!")
        End If
    End Sub
End Class
