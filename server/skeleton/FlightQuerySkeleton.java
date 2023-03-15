package skeleton;

import java.util.Arrays;

import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class FlightQuerySkeleton extends Skeleton{

    public static void handle(byte[] content, char[] clientIP, int port, int requestId)
    {
        //content = Arrays.copyOfRange(content, (int)PrimitiveSizes.sizeof(flightIdSize), (int)(PrimitiveSizes.sizeof(flightIdSize) + content.length - PrimitiveSizes.sizeof(flightIdSize)));

        char[] flightID = SerializePOD.deserializeString(content, 0);

        System.out.println("Flight Number: " + new String(flightID));

    }
}
