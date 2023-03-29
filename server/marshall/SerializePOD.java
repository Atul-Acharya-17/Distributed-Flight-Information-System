package marshall;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import utils.PrimitiveSizes;
import utils.Utils;


/*
    Class that handles marshalling and unmarshalling of Primitive Data Types
    Uses polymorphism (function overloading) to marshall different data types
*/
public class SerializePOD {

    // Everything in java is big-endian
    public static boolean isLittleEndian()
    {
        return false;
    }
    
    public static byte[] serialize(int value)
    {
        byte []buffer = ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putInt(value).array();
        if (SerializePOD.isLittleEndian())
            return Utils.reverse(buffer);

        return buffer;
    }

    public static byte[] serialize(short value)
    {
        byte []buffer = ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putShort(value).array();
        if (SerializePOD.isLittleEndian())
            return Utils.reverse(buffer);

        return buffer;    
    }

    public static byte[] serialize(long value)
    {
        byte []buffer = ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putLong(value).array();
        if (SerializePOD.isLittleEndian())
            return Utils.reverse(buffer);

        return buffer;
    }

    public static byte[] serialize(float value)
    {
        byte []buffer = ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putFloat(value).array();
        if (SerializePOD.isLittleEndian())
            return Utils.reverse(buffer);

        return buffer;    
    }

    public static byte[] serialize(double value)
    {
        byte []buffer = ByteBuffer.allocate((int)(PrimitiveSizes.sizeof(value))).putDouble(value).array();
        if (SerializePOD.isLittleEndian())
            return Utils.reverse(buffer);

        return buffer;    
    }
    
    // For strings we encode the length along with the string contents
    public static byte[] serialize(char[] value)
    {
        byte [] sizeBuffer = serialize((long) value.length);
        byte[] buffer = new byte[value.length + (int)PrimitiveSizes.sizeof((long) value.length)];

        System.arraycopy(sizeBuffer, 0, buffer, 0, sizeBuffer.length);

        for (int i=0; i<value.length; ++i)
        {
            buffer[i + sizeBuffer.length] = (byte) value[i];
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
        byte[] dataBuffer = new byte[(int)PrimitiveSizes.sizeof(value)];
        for (int i=0; i<PrimitiveSizes.sizeof(value); ++i)
        {
            dataBuffer[i] = buffer[start + i];
        }

        if (isLittleEndian()) Utils.reverse(dataBuffer);
        
        return ByteBuffer.wrap(dataBuffer).getInt();
    }

    public static short deserializeShort(byte[] buffer, int start)
    {
        short value = 0;
        byte[] dataBuffer = new byte[(int)PrimitiveSizes.sizeof(value)];
        for (int i=0; i<PrimitiveSizes.sizeof(value); ++i)
        {
            dataBuffer[i] = buffer[start + i];
        }

        if (isLittleEndian()) Utils.reverse(dataBuffer);
        
        return ByteBuffer.wrap(dataBuffer).getShort();
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
        byte[] dataBuffer = new byte[(int)PrimitiveSizes.sizeof(value)];
        for (int i=0; i<PrimitiveSizes.sizeof(value); ++i)
        {
            dataBuffer[i] = buffer[start + i];
        }

        if (isLittleEndian()) Utils.reverse(dataBuffer);
        
        return ByteBuffer.wrap(dataBuffer).getLong();
    }

    public static double deserializeDouble(byte[] buffer, int start)
    {
        long value = deserializeLong(buffer, start);
        double asDouble = Double.longBitsToDouble(value);   

        return asDouble;
    }

    // we deserialize the length first and then the actual string itself
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
