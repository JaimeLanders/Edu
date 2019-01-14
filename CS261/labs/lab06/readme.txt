Overview
--------

For this lab you will think about inheritance (in Object Oriented Design) and
come up with an example where inheritance would be useful. You will not
actually be writing any Java code for this lab. Note: see the information near
the end of these instructions to see how to earn bonus points with this lab.

Details
-------

Inheritance is a very common and useful concept used in Java programming. The
basis for inheritance is in identifying a natural hierarchy between different
types of objects. This natural hierachy involves objects that share common
attributes, actions, or both.

For this lab you are to think of a situation in which you could use
inheritance and describe the hierarchy and each of the classes. Your
description should include some of the shared attributes or actions between
the classes.

Your model must contain at least 5 different classes and at least 3 levels of
hierarchy.

I will provide three examples below to demonstrate the concepts. You cannot
reuse these examples but must make up your own. 

-- Shapes --

The class hierachy for shapes is:

Shape
  PolygonalShape
    Rectangle
  FreeFormShape
    Circle

Shape -- a base class that defines the attributes and actions for all
shapes. For example, all shapes have a name (e.g., square, circle,
etc.). Also, all shapes have an area that can be calcualted with the area()
action.

PolygonalShape -- This is derived from Shape and it represents all shapes that
can be represented as a polygon. The common attributes include a data member
that specifies the number of sides and the lengths of each side.

Rectangle -- This shape is derived from PolygonalShape. It represents a 4
sided shape where all of the corners are right angles. 

FreeFormShape -- This is derived from Shape and it represents a non-polygonal
shape. 

Circle -- This is derived from FreeFormShape and it represents a cirlce.

-- Animals --

The class hierarchy for animals is:

Animal
  Mammal
    Dog
    Cat
  Insect
    Ant

Animal -- The base class for all animals. One common data memmber for all
Animals is a boolean that indicates if the animal is alive or not.

Mammal -- This class is derived from Animal and represents all mammals. All
mammals have 0 or more legs (Dolphins are mammals without legs) so there is a
data member in the mammal class to keep track of the number of legs that a
mammal has.

Dog, Cat -- These classes represent specific types of mammals. They are
different classes between they have slightly different attributes (retractable
claws vs. static claws) and different actions (purr vs. growl).

Insect -- This class, derived from Animal, represents insect animals. Since
all insects have 6 legs, it is not necessary to have a data member that tracks
the number of legs that these objects have.

Ant -- An Ant object derives from the Insect class. Is represents all
different kinds of ants. 

-- Vehicles --

Vehicle
  LandBased
    Car
    Rickshaw
  AirBased
    Jet

Vehicle -- This is the base class for all vehicles. All vehicles have a
current speed.

LandBased -- LandBased vehicles are vehicles that operate on the
ground. 

Car -- This is a subclass of LandBased and represents an engine-powered car.

Rickshaw -- This is a subclass of LandBased and represents a human-powered
push cart.

AirBased -- This class represents all vehicles that operate in the air.

Jet -- This is an AirBased derivative that represents vehicles that use a jet
engine.

Turning in the assignment
-------------------------

Use a text editor to write out your class inheritance in a format simliar to
the examples provided above. Use use the turnin program to turn in your text
file. The command is ~mike.noel/bin/turnin cs261 myclasses.txt.

**** Bonus Points ****
----------------------

This lab can be used to earn bonus points on other assignments in this
class. If you come up with a class hierarchy that is different (in ALL
classes) than any other student's answer then you will get a bonus of 5% that
you can apply to any assignment, quiz, or lab that has been turned in up till
now. This includes the midterm exam that we did last week.

In order to earn the bonus points your class hierachy must be 100% unique. If
there is any overlap in the class names or functions with any classes from any
other student then you will not get the bonus points. 

Your class hiearchy must contain the minimum number of classes and hiearchical
levels as explained in the detailed instructions. Also, each class needs to be
fully explained. If I can't understand your class heirarchy or it is incorrect
or it is not explained, you will not be eligible for the bonus points.

Finally, the format of your text file needs to follow the format I
demonstrated in the three examples above.

To summarize, in order to be eligible for the bonus points you must meet ALL
of the following criteria:

- 100% unique classes and hierarchy
- At least 5 classes and at least 3 hiearchical levels
- Each class fully described
- Your text document in the correct format

If you have any questions, please let me know.



