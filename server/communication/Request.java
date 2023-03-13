package communication;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import marshall.Serialization;
import utils.PrimitiveSizes;

public class Request implements Serialization {
    private int messageType;
    private int requestId;
    private char[] clientIp;
    private byte[] contents;
    private long contentSize;

    public long size()
    {
        return PrimitiveSizes.sizeof(messageType) + PrimitiveSizes.sizeof(requestId) + 2 * PrimitiveSizes.sizeof(contentSize) + clientIp.length + contentSize;
    }

    public byte[] serialize() throws IOException
    {
        byte[] buffer = new byte[(int)this.size() + 1];
        byte[] messageBuffer = ByteBuffer.allocate(4).putInt(messageType).array();
        byte[] requestIdBuffer = ByteBuffer.allocate(4).putInt(requestId).array();
        byte[] clientIpSizeBuffer = ByteBuffer.allocate(8).putLong((long)clientIp.length).array();
        byte[] clientIpBuffer = clientIp.toString().getBytes();
        byte[] contentSizeBuffer = ByteBuffer.allocate(8).putLong(contentSize).array();
        byte[] contentsBuffer = contents;

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream( );
        outputStream.write( messageBuffer );
        outputStream.write( requestIdBuffer );
        outputStream.write( clientIpSizeBuffer );
        outputStream.write( clientIpBuffer );
        outputStream.write( contentSizeBuffer );
        outputStream.write( contentsBuffer );

        buffer = outputStream.toByteArray();

        return buffer;
    }

    public void deserialize(byte[] buffer)
    {
        int start = 0;
        messageType = 0;
        
        for (int i=0; i<4; ++i)
        {
            messageType |= (buffer[start + i] << (8 * i));
        }
        start += PrimitiveSizes.sizeof(messageType);

        requestId = 0;
        for (int i=0; i<4; ++i)
        {
            requestId |= (buffer[start + i] << (8 * i));
        }
        start += PrimitiveSizes.sizeof(messageType);;

        long clientIpSize = 0;
        for (int i=0; i<8; ++i)
        {
            clientIpSize |= (buffer[start + i] << (8 * i));
        }

        start += PrimitiveSizes.sizeof(clientIpSize);;

        clientIp = new char[(int)clientIpSize];

        for (int i=0; i<clientIpSize; ++i)
        {
            clientIp[i] = (char)buffer[start + i];
        }

        start += clientIpSize;

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

    public char[] getClientIp() {
        return clientIp;
    }

    public byte[] getContents() {
        return contents;
    }

    public int getRequestId() {
        return requestId;
    }

    public int getMessageType() {
        return messageType;
    }

    public long getContentSize() {
        return contentSize;
    }

}
