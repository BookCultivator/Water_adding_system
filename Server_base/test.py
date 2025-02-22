import requests

url = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-C0032-001?Authorization=CWA-58ACE3D3-C4F6-4272-862C-DFD7219B46D1&format=JSON"

data = requests.get(url).json() # 將網頁資料GET下來
localtion = data["records"]["location"] # 取得location資料
for i in localtion:
    if i['locationName'] == "臺北市":
        for j in i['weatherElement']:
            if j['elementName'] == "Wx":
                print("weather : {}".format(j['time'][0]['parameter']['parameterName']))

