package communication;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import marshall.Serialization;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class Reply implements Serialization{
    private short status;
    private byte[] contents;
    private long contentSize;

    public byte[] getContents() {
        return contents;
    }

    public Reply(short status, byte[] contents)
    {
        this.status = status;
        this.contents = contents;
        this.contentSize = contents.length;
    }

    public long size()
    {
        return PrimitiveSizes.sizeof(status) + PrimitiveSizes.sizeof(contentSize) + contentSize;
    }

    public byte[] serialize() throws IOException
    {
        byte[] buffer = new byte[(int)this.size()];

        byte[] statusBuffer = SerializePOD.serialize(status);
        byte[] contentSizeBuffer = SerializePOD.serialize((long)contentSize);
        byte[] contentBuffer = contents;

        int i = 0;
        System.arraycopy(statusBuffer, 0, buffer, i, statusBuffer.length);
        i += statusBuffer.length;
        System.arraycopy(contentSizeBuffer, 0, buffer, i, contentSizeBuffer.length);
        i += contentSizeBuffer.length;
        System.arraycopy(contentBuffer, 0, buffer, i, contentBuffer.length);
        i += contentBuffer.length;

        return buffer;
    }

    public void deserialize(byte[] buffer)
    {
        int start = 0;

        status = SerializePOD.deserializeShort(buffer, start);
        start += PrimitiveSizes.sizeof(status);

        contentSize = SerializePOD.deserializeLong(buffer, start);
        start += PrimitiveSizes.sizeof(contentSize);;
        
        contents = new byte[(int)contentSize];
        for (int i=0; i<contentSize; ++i)
        {
            contents[i] = buffer[start + i]; 
        }
    }
}
