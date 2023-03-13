package marshall;

import java.io.IOException;

public interface Serialization {
    public void deserialize(byte[] dataIn);
    public byte[] serialize() throws IOException;
    public long size(); 
}
