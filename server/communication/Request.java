package communication;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

import marshall.Serialization;
import marshall.SerializePOD;
import utils.PrimitiveSizes;
import utils.Utils;

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
        byte[] buffer = new byte[(int)this.size()];

        byte[] messageBuffer = Utils.reverse(ByteBuffer.allocate(4).putInt(messageType).array());
        byte[] requestIdBuffer = Utils.reverse(ByteBuffer.allocate(4).putInt(requestId).array());

        byte[] clientIpSizeBuffer = Utils.reverse(ByteBuffer.allocate(8).putLong((long)clientIp.length).array());
        byte[] clientIpBuffer = new byte[clientIp.length];

        for (int i=0; i<clientIp.length; ++i)
        {
            clientIpBuffer[i] = (byte) clientIp[i];
        }

        byte[] contentSizeBuffer = Utils.reverse(ByteBuffer.allocate(8).putLong(contentSize).array());
        byte[] contentsBuffer = contents;

        System.out.println(clientIpBuffer.length);
        System.out.println(clientIp.length);
        
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
        
        messageType = SerializePOD.deserializeInt(buffer, start);
        start += PrimitiveSizes.sizeof(messageType);

        requestId = SerializePOD.deserializeInt(buffer, start);
        start += PrimitiveSizes.sizeof(requestId);;

        clientIp = SerializePOD.deserializeString(buffer, start);
        long clientIpSize = clientIp.length;
        start += clientIpSize + PrimitiveSizes.sizeof(clientIpSize);

        contentSize = SerializePOD.deserializeLong(buffer, start);
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

    public int getServiceId() {
        return 1;
    }

}
