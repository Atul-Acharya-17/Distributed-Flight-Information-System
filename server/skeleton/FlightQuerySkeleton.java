package skeleton;

import java.io.IOException;
import communication.Reply;
import entities.FlightFactoryServant;
import entities.FlightServant;
import marshall.SerializePOD;

public class FlightQuerySkeleton extends Skeleton{

    public static void handle(byte[] content, char[] clientIP, int port, int requestId) throws IOException
    {
        //content = Arrays.copyOfRange(content, (int)PrimitiveSizes.sizeof(flightIdSize), (int)(PrimitiveSizes.sizeof(flightIdSize) + content.length - PrimitiveSizes.sizeof(flightIdSize)));

        char[] flightID = SerializePOD.deserializeString(content, 0);

        System.out.println("FlightID: ");

        System.out.println("Flight Number: " + new String(flightID));
        FlightFactoryServant fm = new FlightFactoryServant();
        FlightServant fs = (FlightServant) fm.getFlight(new String(flightID));

        short status = 0;
        byte[] replyContent;

        if (fs == null)
        {
            status = 1;
            System.out.println("Here");
            replyContent = SerializePOD.serialize("Flight number does not exist".toCharArray());
        }

        else{
            replyContent = fs.serialize();
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        communication.Communication.send(new String(clientIP), port, replyBuffer);
    }
}
