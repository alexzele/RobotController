package com.example.jochm.robocontr;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {

    TextView t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        t = findViewById(R.id.logoMain);
        t.setText("Press any button to start playing around");

    }

    /*--------------Message picker-------------*/
    public void picker(View view){
        String str = ((Button) view).getText().toString().toLowerCase();
        sendMessage(str);
    }


    /*--------------Server Code----------------*/
    private void sendMessage(final String msg) {
        final String ip = "192.168.1.177";
        final Integer port = 666;


        Thread thread = new Thread (new Runnable() {
            @Override
            public void run() {

                try {
                    //Replace below IP with the IP of that device in which server socket open.
                    //If you change port then change the port number in the server side code also.
                    Socket s = new Socket(ip, port);

                    DataOutputStream out = new DataOutputStream(s.getOutputStream());
                    out.flush();

                    out.writeBytes(msg + "\r");

                    out.close();
                    s.close();

                    //t.setText("message sent");
                    System.out.println("message sent, the server is " + s.isConnected());
                } catch (IOException e) {
                    e.printStackTrace();
                    //t.setText("failed to send message");
                }
            }
        });

        thread.start();
        Log.d("BAR", "thread started");
        while(thread.isAlive()){
            //do nothing
        }
        Log.d("BAR", "thread finished");
        t.setText("Moving " + msg);
    }
}
