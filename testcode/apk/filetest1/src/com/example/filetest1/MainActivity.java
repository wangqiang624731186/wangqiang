package com.example.filetest1;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.widget.Button;
import android.view.View;
import android.view.View.OnClickListener;

public class MainActivity extends Activity {
	@SuppressLint("SdCardPath")
		private Button actionButton;
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	
		actionButton =  (Button)this.findViewById(R.id.action);
		actionButton.setText("start");



		OnClickListener actionButtonListener = new OnClickListener() {
		public void onClick(View v) {
		String path = File.separator + "udisk" + File.separator + "wangqtest";
		System.out.print("--------------------"+ path);
		Log.d("文件不存在",path);
		File file = new File(path);
	
		if(!file.exists())
		{
			try {
				file.createNewFile();
				Log.d("文件不存在", "-----------------------");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				Log.d("文件不存在", "333333-------------------");
				e.printStackTrace();
			}
			Log.d("文件不存在", " 44444444-----------------------");
		}
		try
		{
			OutputStream out =new FileOutputStream(file);
			BufferedOutputStream bout =new BufferedOutputStream(out);
			String str = "test1"; 
			bout.write(str.getBytes());
			bout.close();		  
		}   
		catch (IOException ex) 
		{    
			ex.printStackTrace();   

		}
		}
		};
		actionButton.setOnClickListener(actionButtonListener);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
