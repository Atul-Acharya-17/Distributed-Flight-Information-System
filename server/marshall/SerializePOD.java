package marshall;
import utils.PrimitiveSizes;


// Generics in JAVA expect Object inputs

public class SerializePOD {
    
    public static byte[] serialize(int value)
    {
        return new byte[1];
    }

    public static int deserializeInt(byte[] buffer, int start)
    {
        int value = 0;
        for (int i=0; i<PrimitiveSizes.sizeof(value); ++i)
        {
            value |= (buffer[start + i] << (8 * i));
        }
        return value;
    }

    public static float deserializeFloat(byte[] buffer, int start)
    {
        int value = deserializeInt(buffer, start);
        float asFloat = Float.intBitsToFloat(value);   

        return asFloat;
    }

    public static long deserializeLong(byte[] buffer, int start)
    {
        long value = 0;
        for (int i=0; i<PrimitiveSizes.sizeof(value); ++i)
        {
            value |=  (buffer[start + i] << (8 * i));
        }
        return value;
    }

    public static double deserializeDouble(byte[] buffer, int start)
    {
        long value = deserializeLong(buffer, start);
        double asDouble = Double.longBitsToDouble(value);   

        return asDouble;
    }

    public static char[] deserializeString(byte[] buffer, int start)
    {
        long stringLength = deserializeLong(buffer, start);

        start += PrimitiveSizes.sizeof(stringLength);

        char[] value = new char[(int)stringLength];

        for (int i=0; i<(int)stringLength; ++i)
        {
            value[i] = (char)buffer[start + i];
        }

        return value;
    }
}
