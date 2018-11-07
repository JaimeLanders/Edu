package chocan;
import java.util.*;

public abstract class Data
{
    protected Set<Data> services;
    protected String name;
    protected int number;
    protected String address;
    protected String city;
    protected String state;
    protected int zip;
    protected int id;

    public Data()
    {
//        services = null;
        name = null;
        number = 0;
        address = null;
        city = null;
        state = null;
        zip = 0;
        id = 0;
    }

    public String toString()
    {
        String data = null;

        return data;
    }
}
