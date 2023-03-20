import java.net.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.io.*;

import communication.Communication;
import communication.Request;
import entities.FlightFactoryServant;
import entities.TripServant;
import marshall.SerializePOD;
import skeleton.FlightLocationSkeleton;
import skeleton.FlightQuerySkeleton;
import utils.PrimitiveSizes;

public class Main{

    public static void main(String args[]) throws IOException, ParseException {
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

                contentBuffer = Arrays.copyOfRange(contentBuffer, (int)PrimitiveSizes.sizeof(serviceId), (int)(PrimitiveSizes.sizeof(serviceId) + contentBuffer.length - PrimitiveSizes.sizeof(serviceId)));

                switch(serviceId) {
                    case 1:
                      // code block
                      FlightLocationSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
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
                // FlightFactoryServant fs = new FlightFactoryServant();
                // ArrayList<TripServant> result = fs.planTrip("Muscat", "Singapore", 5, 10000);
                // Collections.sort(result);
                // for (TripServant tripServant : result) {
                //   tripServant.display();
                //   System.out.println();
                // }
                // break;
                
            }
        } finally {if (aSocket != null) aSocket.close();}
    } 
}