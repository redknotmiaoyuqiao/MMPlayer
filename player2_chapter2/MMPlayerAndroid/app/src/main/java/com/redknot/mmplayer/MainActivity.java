package com.redknot.mmplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView num_text = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        num_text = findViewById(R.id.num_text);

        int num = MMPlayerJNI.add(6, 7);

        num_text.setText("Num: " + num);
    }
}