import java.net.*;
import java.util.Arrays;
import java.io.*;

import communication.Communication;
import communication.Request;
import entities.FlightFactoryServant;
import marshall.SerializePOD;
import skeleton.FlightQuerySkeleton;
import utils.PrimitiveSizes;

public class Main{

    public static void main(String args[]) throws IOException {
        FlightFactoryServant ffs = new FlightFactoryServant();
        ffs.populateFlights();

        ffs.displayFlights();

        DatagramSocket aSocket = null;
        try{
            Communication.setup(8080);
            while(true) {
                DatagramPacket messagePacket = Communication.receive();

                byte[] messageByteString = messagePacket.getData();

                int clientPort = messagePacket.getPort();

                Request request = new Request();
                request.deserialize(messageByteString);

                byte[] x = request.serialize();
                System.out.println(x.length);
                request.deserialize(x);

                char[] clientIp = request.getClientIp();
                int requestId = request.getRequestId();

                byte[] contentBuffer = request.getContents();
                int serviceId = SerializePOD.deserializeInt(contentBuffer, 0);

                System.out.println("Content Size:" + request.getContentSize());
                System.out.println("Service ID: " + serviceId);
                System.out.println("Client IP: " + new String(clientIp));

                System.out.println("Client Port: " + messagePacket.getPort());

                contentBuffer = Arrays.copyOfRange(contentBuffer, (int)PrimitiveSizes.sizeof(serviceId), (int)(PrimitiveSizes.sizeof(serviceId) + contentBuffer.length - PrimitiveSizes.sizeof(serviceId)));

                switch(serviceId) {
                    case 1:
                      // code block
                      break;
                    case 2:
                      // code block
                      FlightQuerySkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 3:
                      // code block
                      break;
                    case 4:
                      // code block
                      break;
                    case 5:
                      // code block
                      break;
                    case 6:
                      // code block
                      break;
                    default:
                      // code block
                }
                
                // Communication.send(messagePacket);//new String(clientIp), messagePacket.getPort(), messagePacket.getData());
                // System.out.println(InetAddress.getByName(new String(clientIp)));
            }
        } finally {if (aSocket != null) aSocket.close();}
    } 
}