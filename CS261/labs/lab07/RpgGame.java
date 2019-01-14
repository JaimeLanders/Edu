import java.util.ArrayList;
import weapons.Weapon;
import armor.Armor;
import magic.MagicItem;
import locations.Location;
import locations.cities.City;
import quest.Quest;

public class RpgGame {

    private ArrayList<Weapon> mWeapons = new ArrayList<>();
    private ArrayList<Armor> mArmor = new ArrayList<>();
    private ArrayList<MagicItem> mMagic = new ArrayList<>();
    private ArrayList<Location> mLocations = new ArrayList<>();
    private ArrayList<City> mCities = new ArrayList<>();
    private ArrayList<Quest> mQuests = new ArrayList<>();

    public void play() {
	System.out.println("Ready to play.");

	System.out.println("Game over.");
    }

    public RpgGame() {

    }

    public static void main(String[] args) {
	
	RpgGame game = new RpgGame();

	game.play();
    }	
}
