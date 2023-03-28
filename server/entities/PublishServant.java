package entities;

import java.io.IOException;

import marshall.SerializePOD;
import utils.PrimitiveSizes;

/* 
    Servant class for Publisher interface.
    Defines state variables for class including update message.
    Implements methods including getters and setters, and marshalling-unmarshalling.
*/
public class PublishServant implements Publish{
    private char[] msg;

    @Override
    public long size()
    {
        return(
        PrimitiveSizes.sizeof((long) msg.length) + msg.length
            );
    }

    @Override
    public void deserialize(byte[] dataIn) {
        int start = 0;
        msg = SerializePOD.deserializeString(dataIn, start);
    }

    @Override
    public byte[] serialize() throws IOException {
        byte[] buffer = new byte[(int) this.size()];
        byte[] msgBuffer = SerializePOD.serialize(msg);

        int i = 0;
        System.arraycopy(msgBuffer, 0, buffer, i, msgBuffer.length);
        i += msgBuffer.length;

        return buffer;
    }

    @Override
    public char[] getMsg() {
        return this.msg;
    }

    @Override
    public void setMsg(char[] msg) {
        this.msg = msg;
    }
}
