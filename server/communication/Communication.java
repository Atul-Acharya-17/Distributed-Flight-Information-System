package communication;

import java.net.*;
import java.io.*;

public class Communication {
    static DatagramSocket aSocket = null;

    public static void setup(int port) throws SocketException
    {
        aSocket = new DatagramSocket(port);
        Socket s = new Socket();
        try {
            s.connect(new InetSocketAddress("google.com", 80));
            System.out.print(s.getLocalAddress());
            s.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static void send(String ip, int port, byte[]message) throws IOException
    {
        DatagramPacket packet = new DatagramPacket(message, message.length, InetAddress.getByName(ip), port);
        aSocket.send(packet);
    }

    public static void send(DatagramPacket messagePacket) throws IOException
    {
        aSocket.send(messagePacket);
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
