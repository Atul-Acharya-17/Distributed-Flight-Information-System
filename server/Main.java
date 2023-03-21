import java.net.*;
import java.util.Arrays;
import java.io.*;

import communication.Communication;
import communication.Request;
import entities.BookingFactory;
import entities.FlightFactory;
import entities.FlightFactoryServant;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import skeleton.CancelReservationSkeleton;
import skeleton.CheckReservationSkeleton;
import skeleton.FlightLocationSkeleton;
import skeleton.FlightQuerySkeleton;
import skeleton.NewReservationSkeleton;
import skeleton.TripPlanSkeleton;
import utils.PrimitiveSizes;

public class Main{

    public static void main(String args[]) throws IOException {
        FlightFactory ffs = new FlightFactoryServant();
        ffs.populateFlights();
        ffs.displayFlights();
        
        BookingFactory bfs = new BookingFactoryServant();
        bfs.populateBookings();

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
                      TripPlanSkeleton.handle(contentBuffer, clientIp, clientPort, requestId);
                      break;
                    default:
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