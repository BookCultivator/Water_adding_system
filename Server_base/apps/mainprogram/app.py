from flask import Flask, render_template, jsonify, url_for, request
import random

app = Flask(__name__, static_url_path='/apps/mainprogram/views', static_folder='views') # 設定靜態檔案路徑

@app.route("/", methods = ["GET"]) # 設定路由
def index():
    return  '''
                <!DOCTYPE html>
                <html>
                <head>
                <script>
                document.location.href = "/apps/mainprogram/views/FrontPage.html";
                </script>
                </head>
                <body>
                </body>
                </html>
            ''', 200

@app.route("/interface/web_extremity", methods = ["GET"])
def Web_Extremity_handle():
    return "Hi"

@app.route("/interface/phone_extremity", methods = ["GET"])
def Phone_Extremity_handle():
    return "Hi"

@app.route("/api/bot/line_bot", methods = ["GET"])
def Line_bot_handle():
    return "Hi"

@app.route("/api/data/sensor_data", methods = ["POST"])
def Sensor_Data_handle():
    return "Hi"

@app.route("/IOT/IoT_data", methods = ["POST"])
def IoT_Data_handle():
    return "Hi"

@app.route('/IOT/IoT_page/<string:id>', methods=['GET'])
def say_hi(id):
    return jsonify(message="{}".format(id))

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

