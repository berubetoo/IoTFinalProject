package com.example.smartlocker

import android.app.Activity
import android.os.Bundle
import android.widget.Button
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.smartlocker.ui.theme.SmartLockerTheme
import com.google.firebase.Firebase
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.database

class MainActivity : Activity()
{
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)

//        val database = Firebase.database

        val button = findViewById<Button>(R.id.toggleDoorButton)

        val database = FirebaseDatabase.getInstance()
        val doorRef = database.getReference("doorStatus")

        button.setOnClickListener {
            doorRef.get().addOnSuccessListener { snapshot ->
                val currentStatus = snapshot.getValue(Int::class.java) ?: 0 // default, the door is closed
                if (currentStatus == 1)
                {
                    doorRef.setValue(0)
                    button.text = "OPEN"
                }
                else
                {
                    doorRef.setValue(1)
                    button.text = "CLOSE"
                }
            }
        }
    }
}