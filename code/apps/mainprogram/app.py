from flask import Flask, render_template, jsonify, url_for, request
import random

app = Flask(__name__)

@app.route("/", methods=["GET"]) # 設定路由
def test():
    return "Hello World"

@app.route("/test2/<name>", methods=["GET"], endpoint="prinnNameEndpoint")
def test2(name):
    return f"<h1> {name} </h1>"

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

@app.route("/test4/<name>", methods=["GET"])
def test4(name):
    return render_template("index.html", name=name)

# while app.test_request_context():
#     print(url_for('test2', name='test2'))
#     print(url_for('test4', name='dd', page=1))
    

if __name__ == '__main__':
    app.run(debug=True)

