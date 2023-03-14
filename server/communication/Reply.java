package communication;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import marshall.Serialization;
import utils.PrimitiveSizes;

public class Reply implements Serialization{
    private short status;
    private byte[] contents;
    private long contentSize;

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
        byte[] buffer = new byte[(int)this.size() + 1];

        byte[] statusBuffer = ByteBuffer.allocate(4).putInt(status).array();
        byte[] contentSizeBuffer = ByteBuffer.allocate(8).putLong(contentSize).array();
        byte[] contentsBuffer = contents;

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream( );
        outputStream.write(statusBuffer);
        outputStream.write( contentSizeBuffer );
        outputStream.write( contentsBuffer );

        buffer = outputStream.toByteArray();

        return buffer;
    }

    public void deserialize(byte[] buffer)
    {
        int start = 0;

        status = 0;
        
        for (int i=0; i<4; ++i)
        {
            status |= (buffer[start + i] << (8 * i));
        }
        start += PrimitiveSizes.sizeof(status);

        contentSize = 0;
        for (int i=0; i<8; ++i)
        {
            contentSize |= (buffer[start + i] << (8 * i));
        }

        start += PrimitiveSizes.sizeof(contentSize);;
        
        contents = new byte[(int)contentSize];
        for (int i=0; i<contentSize; ++i)
        {
            contents[i] = buffer[start + i]; 
        }
    }

    public byte[] getContents() {
        return contents;
    }
}
