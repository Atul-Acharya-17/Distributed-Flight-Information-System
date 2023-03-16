package marshall;
import java.nio.ByteBuffer;

import utils.PrimitiveSizes;
import utils.Utils;

// Generics in JAVA expect Object inputs

public class SerializePOD {
    
    public static byte[] serialize(int value)
    {
        return Utils.reverse(ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putInt(value).array());
    }

    public static byte[] serialize(long value)
    {
        return Utils.reverse(ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putLong(value).array());
    }

    public static byte[] serialize(float value)
    {
        return Utils.reverse(ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putFloat(value).array());
    }

    public static byte[] serialize(double value)
    {
        return Utils.reverse(ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putDouble(value).array());
    }

    public static byte[] serialize(char[] value)
    {
        byte[] buffer = new byte[value.length];

        for (int i=0; i<value.length; ++i)
        {
            buffer[i] = (byte) value[i];
        }
        
        return buffer;
    }

    public static byte[] serialize(String value)
    {
        return SerializePOD.serialize(value.toCharArray());
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
