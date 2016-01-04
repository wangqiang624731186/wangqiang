package com.android.tests.testsensors;

import android.R.string;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.util.Log;

public class dbHelper extends SQLiteOpenHelper {


	public final static String FIELD_ID="_id"; 

	private String mName;
	
	public dbHelper(Context context, String name, CursorFactory factory,int version)
	{
		super(context, name+".db", factory, version);
		mName = name;
	}

	//创建数据库
	public void onCreate(SQLiteDatabase db) {
		Log.i(mName,"create a Database");
		//创建数据库sql语句
		String sql="Create table "+mName+"("+FIELD_ID+" integer primary key autoincrement,"
		+mName+" text );";
		//执行创建数据库操作
		db.execSQL(sql);
	}


	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		// TODO Auto-generated method stub
		String sql=" DROP TABLE IF EXISTS "+mName;
		db.execSQL(sql);
		onCreate(db);
	}


	
	public long insert(String Title)
	{
		SQLiteDatabase db=this.getWritableDatabase();
		ContentValues cv=new ContentValues(); 
		cv.put(mName, Title);
		long row=db.insert(mName, null, cv);
		return row;
	}
	
}
