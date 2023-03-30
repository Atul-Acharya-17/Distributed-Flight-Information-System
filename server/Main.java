import java.net.*;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.io.*;

import communication.Communication;
import communication.Request;
import entities.BookingFactory;
import entities.FlightFactory;
import entities.FlightFactoryServant;
import entities.TripServant;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import skeleton.CancelReservationSkeleton;
import skeleton.CheckReservationSkeleton;
import skeleton.FlightLocationSkeleton;
import skeleton.FlightPublisherSkeleton;
import skeleton.FlightQuerySkeleton;
import skeleton.NewReservationSkeleton;
import skeleton.Skeleton;
import skeleton.TripPlanSkeleton;
import utils.PrimitiveSizes;

public class Main{
  
    public static void main(String args[]) throws IOException {

        int serverType = Integer.parseInt(args[0]);

        // Type 0 for Atmost Once and any other number of Atleast Once

        if (serverType != 0)
        {
          System.out.println("Using Atleast Once Server\n");
          Skeleton.setServertype(Skeleton.ServerType.ATLEAST_ONCE);
        }

        else
        {
          System.out.println("Using Atmost Once Server\n");
          Skeleton.setServertype(Skeleton.ServerType.ATMOST_ONCE);

        }
      
        FlightFactory ffs = new FlightFactoryServant();
        ffs.populateFlights();
        // ffs.displayFlights();
        
        BookingFactory bfs = new BookingFactoryServant();
        bfs.populateBookings();

        DatagramSocket aSocket = null;
        try{
            Communication.setup(8080);
            while(true) {
                DatagramPacket messagePacket = Communication.receive();

                double probability = Math.random();

                if (probability < 0.1) 
                {
                  System.out.println("Dropping Message");
                  continue;
                }

                byte[] messageByteString = messagePacket.getData();

                int clientPort = messagePacket.getPort();

                Request request = new Request();
                request.deserialize(messageByteString);

                String clientIp = new String(request.getClientIp());
                int requestId = request.getRequestId();

                byte[] contentBuffer = request.getContents();
                int serviceId = SerializePOD.deserializeInt(contentBuffer, 0);

                contentBuffer = Arrays.copyOfRange(contentBuffer, (int)PrimitiveSizes.sizeof(serviceId), (int)(PrimitiveSizes.sizeof(serviceId) + contentBuffer.length - PrimitiveSizes.sizeof(serviceId)));

                switch(serviceId) {
                    case 1:
                      FlightLocationSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 2:
                      FlightQuerySkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      // ffs.populateFlights();     // For experimentation purposes           
                      break;
                    case 3:
                      NewReservationSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 4:
                      CancelReservationSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 5:
                      CheckReservationSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 6:
                      FlightPublisherSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    case 7:
                      TripPlanSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);                      
                      break;
                    default:
                } 
            }
        } finally {if (aSocket != null) aSocket.close();}
    } 
}