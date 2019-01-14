import java.util.Scanner;

public class Sensor
{
    private ElementType element;
    private double value;

    public Sensor(Scanner sc)
    {
        this.element = ElementType.valueOf(sc.next()); 
        this.value = sc.nextDouble(); 
    }

    public Sensor(ElementType elementIn, double valueIn)
    {
        this.element = elementIn;
        this.value = valueIn; 
    }

    public ElementType getElement()
    {
        return this.element;
    }

    public double getValue()
    {
        return this.value;
    }

    public void setElement(ElementType elementIn)
    {
        this.element = elementIn;
    }

    public void setValue (double valueIn)
    {
        this.value = valueIn;
    }
}
