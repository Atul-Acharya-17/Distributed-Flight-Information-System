package communication;

import java.net.*;
import java.io.*;

public class Communication {
    static DatagramSocket aSocket = null;

    public static void setup(int port) throws SocketException
    {
        aSocket = new DatagramSocket(port);
    }

    public static void send(DatagramPacket message) throws IOException
    {
        aSocket.send(message);
    }

    public static DatagramPacket receive() throws IOException
    {
        byte[] buffer = new byte[1000];
        DatagramPacket request = new DatagramPacket(buffer, buffer.length);
        aSocket.receive(request); //blocked if no input

        return request;
    }

    public static void close()
    {
        if (aSocket != null) aSocket.close();
    }
}
