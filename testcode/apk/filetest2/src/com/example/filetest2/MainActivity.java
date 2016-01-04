package com.example.filetest2;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		File file = new File("/extsd/wangqtest");
		if(!file.exists())
		{
			Log.d("文件不存在", "-------------------------");
		}
		try
		{
			InputStream in = new FileInputStream(file);
			BufferedInputStream bin = new BufferedInputStream(in);
			
			byte[] b = new byte[100];
			int len = bin.read(b);
		
			System.out.print(b.toString());
			
			Log.d("文件不存在", " 1111111111111111111111111---------------------------");
			OutputStream out =new FileOutputStream(file);
			Log.d("文件不存在", " 22222222222222222222222222222------------------------");
			BufferedOutputStream bout =new BufferedOutputStream(out);
			Log.d("文件不存在", " 3333333333333333333333333333333-------------------------");
			String str = "test2" + new String(b, 0, len, "utf-8");; 
			bout.write(str.getBytes());
			Log.d("文件不存在", " 444444444444444444444444444444444444------------------------");
			bout.close();	
			Log.d("文件不存在", " 5555555555555555555555555555555555555555-------------------------");
		}   
		catch (IOException ex) 
		{    Log.d("文件不存在", " 666666666666666666666666666666666666i-------------------------");
			ex.printStackTrace();   

		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
