import java.io.FileNotFoundException;
import java.io.StringReader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class getEntitiesFromJSON {
	public static void main(String[] args) {

		BufferedReader br = null;

		try {
			br = new BufferedReader(new FileReader("./tweetsLacEntities.txt"));
			String sCurrentLine;
			while ((sCurrentLine = br.readLine()) != null) 
			{

				JSONParser parser = new JSONParser();

				Object obj = parser.parse(new StringReader(sCurrentLine));

				JSONObject jsonObject = (JSONObject) obj;

				// loop array
				JSONArray ann = (JSONArray) jsonObject.get("annotations");
				Iterator<JSONObject> iterator = ann.iterator();
				while (iterator.hasNext()) {
					JSONObject curr = iterator.next();
					String title = (String) curr.get("title");
					String r = (String) curr.get("rho");
					float rho = Float.parseFloat(r);
					if(rho>0.08)	
						System.out.print(title+',');

				}
				System.out.println();
			}

		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}

	}

}
