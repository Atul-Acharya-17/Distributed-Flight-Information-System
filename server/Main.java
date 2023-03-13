import java.net.*;
import java.io.*;

import communication.Communication;
import communication.Request;

public class Main{
    public static void main(String args[]) throws IOException{
        DatagramSocket aSocket = null;
        try{
            Communication.setup(8080);
            while(true) {
                DatagramPacket message = Communication.receive();

                // System.out.println(request.getAddress());

                // Request request = new Request();
                // request.deserialize(message.getData());


                //Unmarshall Request

                // Get Service ID
                // Depending on Service ID call the correct Proxy methods

                Communication.send(message);
            }
        }finally {if (aSocket != null) aSocket.close();}
    } 
}