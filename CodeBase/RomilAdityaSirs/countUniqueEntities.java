import java.io.FileNotFoundException;
import java.io.StringReader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.TreeMap;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class countUniqueEntities {
	public static void main(String[] args) {

		TreeMap<String, String> tm = new TreeMap<String, String>();
		BufferedReader br = null;
		int count=0;

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
					{

						count++;
						try
						{
							tm.put(title,"1");
						}
						catch(NullPointerException e)
						{
							System.out.println("Here");
							continue;
						}
					}
				}
			}

		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		System.out.println(count);
		System.out.println(tm.size());

	}

}
