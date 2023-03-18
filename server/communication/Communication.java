package communication;

import java.net.*;
import java.io.*;

public class Communication {
    static DatagramSocket aSocket = null;

    public static void setup(int port) throws SocketException
    {
        aSocket = new DatagramSocket(port);
    }

    public static void send(String ip, int port, byte[]message) throws IOException
    {
        System.out.println("Sending to : " + ip + ":" + port);
        System.out.println(message.length);
        DatagramPacket packet = new DatagramPacket(message, message.length, InetAddress.getByName(ip), port);
        aSocket.send(packet);
    }

    public static void send(DatagramPacket messagePacket) throws IOException
    {
        System.out.println("Length of packet: " + messagePacket.getLength());

        for (int i=0; i<messagePacket.getLength(); ++i)
        {
            System.out.println((int) messagePacket.getData()[i]);
        }
        System.out.println(messagePacket.getPort());
        System.out.println(messagePacket.getAddress());
        //System.out.println((int)messagePacket.getData()[messagePacket.getLength()]);
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
