package entities;

import marshall.Serialization;

public interface Publish extends Serialization {
    
    public char[] getMsg();

    public void setMsg(char[] msg);
}
