import requests


# 取得天氣資訊
def Search_weather(city):
    url = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-C0032-001?Authorization=CWA-58ACE3D3-C4F6-4272-862C-DFD7219B46D1&format=JSON"
    data = requests.get(url).json() # 將網頁資料GET下來
    location = data["records"]["location"] # 取得location資料
    print("城市 : {}".format(city))
    for i in location:
        if i['locationName'] == city:
            for j in i['weatherElement']:
                if j['elementName'] == "Wx":
                    print("Time : {}".format(j['time'][0]['startTime']))
                    print("天氣狀況 : {}".format(j['time'][0]['parameter']['parameterName']))
            for j in i['weatherElement']:
                if j['elementName'] == "MaxT":
                    print("最高溫度 : {}".format(j['time'][0]['parameter']['parameterName']), "°C")
            for j in i['weatherElement']:
                if j['elementName'] == "MinT":
                    print("最低溫度 : {}".format(j['time'][0]['parameter']['parameterName']), "°C")
            for j in i['weatherElement']:
                if j['elementName'] == "CI":
                    print("舒適度   : {}".format(j['time'][0]['parameter']['parameterName']))
            for j in i['weatherElement']:
                if j['elementName'] == "PoP":
                    print("降雨機率 : {}".format(j['time'][0]['parameter']['parameterName']), "%")
    print("=====================================")


Search_weather("臺北市")
Search_weather("臺南市")

