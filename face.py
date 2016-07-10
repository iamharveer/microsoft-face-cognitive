import http.client, urllib.request, urllib.parse, urllib.error, base64
import sys, json

if (len(sys.argv) < 2):
    print ("Pass paths to two images as cmd parameters");
    sys.exit(-1);


def detect_faces (fileObject):

    fileOb = open (fileObject, "rb");

    headers = {
        # Request headers
        'Content-Type': 'application/octet-stream',
        'Ocp-Apim-Subscription-Key': '8cd5ddb7bae141e1a2094d8941b36df7',
    }

    params = urllib.parse.urlencode({
        # Request parameters
        'returnFaceId': 'true',
        'returnFaceLandmarks': 'false',
        'returnFaceAttributes': 'age,gender',
    })

    try:
        conn = http.client.HTTPSConnection('api.projectoxford.ai')
        conn.request("POST", "/face/v1.0/detect?%s" % params, fileOb, headers)
        response = conn.getresponse()
        data = response.read()
        decoded_data = data.decode ("UTF-8");
        conn.close();

    except Exception as e:
        print("[Errno {0}] {1}".format(e.errno, e.strerror));

    return json.loads(decoded_data);

def face_matches (jsonObj):
    headers = {
        # Request headers
        'Content-Type': 'application/json',
        'Ocp-Apim-Subscription-Key': '8cd5ddb7bae141e1a2094d8941b36df7',
    }

    try:
        conn = http.client.HTTPSConnection('api.projectoxford.ai')
        conn.request("POST", "/face/v1.0/verify", jsonObj, headers)
        response = conn.getresponse()
        data = response.read()
        decoded_data = data.decode ("UTF-8");
        conn.close()

    except Exception as e:
        print("[Errno {0}] {1}".format(e.errno, e.strerror))

    return json.loads(decoded_data);

image1 = detect_faces (sys.argv[1]);
image2 = detect_faces (sys.argv[2]);

faceId1 = image1[0]['faceId'];
faceId2 = image2[0]['faceId'];

# Create Json object to be sent over for verification.
str1 = '{"faceId1":"' + faceId1 + '", '  + '"faceId2":"' + faceId2 + '"}'
jsonObj = json.loads(str1);

res = face_matches (str(jsonObj));
print ("Image matched : %s" % res['isIdentical']);

age1= image1[0]['faceAttributes']['age'];
age2= image2[0]['faceAttributes']['age'];
age = (age1 + age2) / 2;

gender = image1[0]['faceAttributes']['gender'];

print ("Person is %s of age %.1f" %(gender, age));
