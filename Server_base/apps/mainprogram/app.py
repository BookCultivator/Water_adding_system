from flask import Flask, render_template, jsonify, url_for, request
import random



app = Flask(__name__) # 設定靜態檔案和模板檔案的路徑

@app.route("/", methods = ["GET"]) # 設定路由
def index_handle():
    return "Hello. This page is nothing."

@app.route("/interface/web_extremity", methods = ["GET"])
def Web_Extremity_handle():
    return "Hi"

@app.route("/interface/phone_extremity", methods = ["GET"])
def Phone_Extremity_handle():
    return "Hi"

@app.route("/bot/line_bot", methods = ["GET"])
def Line_bot_handle():
    return "Hi"

@app.route("/bot/discord_bot", methods = ["GET"])
def Discord_bot_handle():
    return "hi"

@app.route("/data/sensor_data", methods = ["POST"])
def Sensor_Data_handle():
    return "Hi"


# # 模擬獲取即時溫度
# def get_temperature():
#     return round(random.uniform(20.0, 30.0), 2)

# @app.route("/test3", methods=["GET"])
# def test3():
#     return render_template("index.html")

# @app.route('/temperature')
# def temperature():
#     # 返回模擬的溫度數據
#     return jsonify({'temperature': get_temperature()})


if __name__ == '__main__':
    app.run(debug=True)

