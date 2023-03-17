package communication;
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
        return (
            PrimitiveSizes.sizeof(messageType) + 
            PrimitiveSizes.sizeof(requestId) + 
            PrimitiveSizes.sizeof(clientIp.length) + clientIp.length + 
            PrimitiveSizes.sizeof(contentSize) + contentSize
        );
    }

    public byte[] serialize() throws IOException
    {
        byte[] buffer = new byte[(int)this.size()];

        byte[] messageBuffer = SerializePOD.serialize(messageType);
        byte[] requestIdBuffer = SerializePOD.serialize(requestId);

        byte[] clientIpSizeBuffer = SerializePOD.serialize((long)clientIp.length);
        byte[] clientIpBuffer = SerializePOD.serialize(clientIp);

        byte[] contentSizeBuffer = SerializePOD.serialize(contentSize);
        byte[] contentsBuffer = contents;

        System.out.println(clientIpBuffer.length);
        System.out.println(clientIp.length);
        
        int i = 0;
        System.arraycopy(messageBuffer, 0, buffer, i, messageBuffer.length);
        i += messageBuffer.length;
        System.arraycopy(requestIdBuffer, 0, buffer, i, requestIdBuffer.length);
        i += requestIdBuffer.length;
        System.arraycopy(clientIpSizeBuffer, 0, buffer, i, clientIpSizeBuffer.length);
        i += clientIpSizeBuffer.length;
        System.arraycopy(clientIpBuffer, 0, buffer, i, clientIpBuffer.length);
        i += clientIpBuffer.length;
        System.arraycopy(contentSizeBuffer, 0, buffer, i, contentSizeBuffer.length);
        i += contentSizeBuffer.length;
        System.arraycopy(contentsBuffer, 0, buffer, i, contentsBuffer.length);
        i += contentsBuffer.length;

        return buffer;
    }

    public void deserialize(byte[] buffer)
    {
        int start = 0;
        messageType = 0;
        
        messageType = SerializePOD.deserializeInt(buffer, start);
        start += PrimitiveSizes.sizeof(messageType);

        requestId = SerializePOD.deserializeInt(buffer, start);
        start += PrimitiveSizes.sizeof(requestId);

        clientIp = SerializePOD.deserializeString(buffer, start);
        long clientIpSize = clientIp.length;
        start += clientIpSize + PrimitiveSizes.sizeof(clientIpSize);

        contentSize = SerializePOD.deserializeLong(buffer, start);
        start += PrimitiveSizes.sizeof(contentSize);
        
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
