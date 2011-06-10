package com.android.androidgldemos;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;
import android.widget.ArrayAdapter;
import android.content.Intent;
import android.util.Log;

//import com.android.androidgldemos.TestIntent;

public class AndroidGLDemosAct extends ListActivity
{

	private static final String TAG = "AndroidGLDemoAct";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.main);

        setListAdapter(new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, mStrings));
        getListView().setTextFilterEnabled(true);
    }

    private String[] mStrings = {
            "Triangle", "Texture", "Blending", "Light & Material",  "Caustics", "Flag", "Water", "Fire", "Sea", "RoundCube",  
	};

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {

		Log.d (TAG, "Item " + position + " is clicked.\n");

        try {

			switch (position) {
				case Constants.TRIANGLEID: //Triangle
            		//Intent demoInt = new Intent(this, TriangleAct.class);
            		//Intent demoInt = new Intent(this, TestIntent.class);
            		//demoInt.putExtra("id", channelId);
            		//startActivity(demoInt);	
            		startActivity(new Intent(this, TriangleAct.class));	
					break;
				case Constants.TEXTUREID: //Texture
            		//Intent demoInt = new Intent(this, TextureAct.class);
            		//startActivity(demoInt);	
					startActivity(new Intent(this, TextureAct.class));
					break;

				case Constants.BLENDINGID: //Blending
					startActivity(new Intent(this, BlendingAct.class));
					break;

				case Constants.LIGHTMATERIALID: //AndMii
					startActivity(new Intent(this, AndMiiAct.class));
					break;

				case Constants.CAUSTICSID: //Caustics
					startActivity(new Intent(this, CausticsAct.class));
					break;

				case Constants.FLAGID: //Flag
					startActivity(new Intent(this, FlagAct.class));
					break;

				case Constants.WATERID: //Water
					startActivity(new Intent(this, WaterAct.class));
					break;



			}
	


        } catch (Exception e) {
            System.out.println (e.getMessage());
        }


/*
        Map map = (Map) l.getItemAtPosition(position);

        Intent intent = (Intent) map.get("intent");
        startActivity(intent);
*/
    }


}
