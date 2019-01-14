import java.util.Scanner;

public class Emitter 
{
    private ElementType element;
    private double value;

    public Emitter(Scanner sc)
    {
        this.element = ElementType.valueOf(sc.next());
        this.value = sc.nextDouble();
    }

    public Emitter(ElementType elementIn, double valueIn)
    {
        element = elementIn;
        value = valueIn;

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
