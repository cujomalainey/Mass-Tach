package main

import (
        "os"
        "fmt"
        "sync"

        "github.com/eclipse/paho.mqtt.golang"
        "github.com/gin-gonic/gin"
)

func main() {
        server := os.Getenv("MQTT_BROKER")

        opts := mqtt.NewClientOptions().AddBroker(server)
        client := mqtt.NewClient(opts)

        if token := client.Connect(); token.Wait() && token.Error() != nil {
                fmt.Errorf("Failed to connect to server %s", server)
                return
        }

        fmt.Printf("Connected to %s\n", server)

        r := gin.Default()
        r.GET("/ping", func(c *gin.Context) {
                token := client.Publish("test", 0, false, "ping")
                token.Wait()
                var returnCode int
                var message string
                if token.Error() != nil {
                        returnCode = 500
                        message = fmt.Sprintf("%v", token.Error())
                } else {
                        returnCode = 200
                        message = fmt.Sprintf("Ping sent to %s", server)
                }
                c.JSON(returnCode, gin.H{
                        "message": message,
                })
        })
        r.Run()
}
