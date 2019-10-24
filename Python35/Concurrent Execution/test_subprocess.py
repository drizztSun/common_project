import subprocess
import urllib
from multiprocessing import pool

# stdout, stderr could be subprocess.PIPE, subprocess.DEVNULL

def test_subprocess_basic():

    try:
        completed = subprocess.run([
            'curl',
            '-X',
            'POST',
            '-H',
            '\"Content-Type: application/json\"',
            '-H',
            '\"Cookie: dps-signal-cookie=eyJ0eXAiOiJKV1QiLCJ4NWMiOlsiTUlJRkZqQ0NBdjZnQXdJQkFnSUpBSlFSN3h0ek9hbmxNQTBHQ1NxR1NJYjNEUUVCQ3dVQU1JR2ZNUXN3Q1FZRFZRUUdFd0pWVXpFV01CUUdBMVVFQ0F3TlRXRnpjMkZqYUhWelpYUjBjekVTTUJBR0ExVUVCd3dKUTJGdFluSnBaR2RsTVJ3d0dnWURWUVFLREJOQmEyRnRZV2tnVkdWamFHNXZiRzluYVdWek1Rd3dDZ1lEVlFRTERBTkxUVWt4R1RBWEJnTlZCQU1NRUVWQlFTQkVaWFpwWTJVZ1EwRWdSekV4SFRBYkJna3Foa2lHOXcwQkNRRVdEbXR0YVVCaGEyRnRZV2t1WTI5dE1CNFhEVEU1TURneE5URXhNamMwTlZvWERUSXdNRGd4TlRFeE1qYzBOVm93Z2FVeEN6QUpCZ05WQkFZVEFsVlRNUll3RkFZRFZRUUlEQTFOWVhOellXTm9kWE5sZEhSek1SSXdFQVlEVlFRSERBbERZVzFpY21sa1oyVXhIREFhQmdOVkJBb01FMEZyWVcxaGFTQlVaV05vYm05c2IyZHBaWE14RERBS0JnTlZCQXNNQTB0TlNURWZNQjBHQTFVRUF3d1dSVUZCSUVSbGRtbGpaU0JEWlhKMGFXWnBZMkYwWlRFZE1Cc0dDU3FHU0liM0RRRUpBUllPYTIxcFFHRnJZVzFoYVM1amIyMHdnZ0VpTUEwR0NTcUdTSWIzRFFFQkFRVUFBNElCRHdBd2dnRUtBb0lCQVFET0lhZXhrWE5qdU5zdWFibDQxZml3eG9jQVNST3Y0SVJFZVd0aGJJT1VEcVdPaytxdzlzSFB0ZWxNdGFVc055emx0MlRmaTVlNlBGMXhUZXdrQnk3QUVGTE8vZEQwS2hvd1ZHbTdFendyYjNrQ2VROEI3Rld6ZGFCQis0c25nbk9ZVk9UQ3ZOMWFFTnYwQlZtTWVBN2NkbjlCMlpVTkhaaGRobytZRmNQQ3VWWGJoZm9zYWRnM2xMQlluOWhuSVlyLzJNK01samtwbkJPN2xMTlBNVmtoRGxMZU9lY0llaEgzdmJiSStZeDIxRU1ISmVFSytsNlorbnV1WXZWR0diNlV4M3Q1NVFRU1NJZElWWG5KQi9ocWVaRlhib2dMcWdUT0VOVS9PR3d1Y2hJRlJYd1NwelpMZzdRL2dWZStiSmx3VE5aUnZUQitIN0prZFM0NWlwdDFBZ01CQUFHalRUQkxNQWtHQTFVZEV3UUNNQUF3SFFZRFZSME9CQllFRk9KU3p1WXVHQ053MktZenlCNmlGcFAvbC9WeE1COEdBMVVkSXdRWU1CYUFGTnQrSHg3dnNVdXU4dElHWm1aekVuVXFBSUlyTUEwR0NTcUdTSWIzRFFFQkN3VUFBNElDQVFBV2JvVWQ5eHp1NGVxQndrbmFhVkVZUkUyZHQ5Q2hPSkZhMEtBcGREUHF1d3ZodW5NRDVPUzBEcFl1VHhRWTZpYnRnTjBRVi9pL2MvaVRENk9ZeFNnbXJDdnp5L1AwYk94NlZ3RFBpVi9Ka1BMUjU0NzlwbjNyZVplb0pNMWw4VmVyMm51VWp0dFpIRFlNTWE0TFIzdnJrUEhpK1o5S1QvRjVyU1E4aHZRNGRSQXIyUEduQjltQzY3S3IxZldaR2VHbDNCZnlIRWY2M2gwWm1OWHVQakthSml5eTdYODAxbzVheTBWRlNQV3VsZlBGemlzNkdLNmdNVFYwQ00vTCtQK3U3dFZoTnBkaE5CVzRoSnRDMmswbWlSZ2RORXJqMlBjOGJITmkxRko0RnZydnF6elZuUUVxYWYybnVhWWNndDBETVh6K3YvdFlkN2tPbENBVFEwNUloL09EYTJxMnUvRU9xUFNTUFJwSThiSlQrN0RyUGpXTTB5K0ZQOHhEdWt3MUNYLzM2WHZERUhuZWd2ZWlJZiszQWNIZjMxZE4rRnV5VHR0cnFZckVmSHVGbWlRbm1vUFF2U21GOUlLMHRhcTM2UUJyYUNKaDBUZ0RjZGV1Nmg3Tm9ZVVJsRXF5dG56blk3RXRuMk0wTUx3UG5qWDZkV0Y2VWFWUnBLMGFKUzNSait6SC9RMVB6WlNIanBSUDd5YnJsZDA0SWZVREVuVG9wdmFqVTZ1ZjdTbUtpRTFPTFJ0S05VaWt4N3ZMREVCQ1RpV1JIcXdud0ZKcG5Vc3pBNlJ6bXhFRkxQVUsvM2w0Zjl0MHkvbk9MQ0FHc3NyREZ1WUVya09mYzhWRlltMzVKeEZmNWtDa3lTbTM0NUtpL3dlVk5UemxFZW0veUNtaG95YjduNlhwdGc9PSJdLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJodHRwczovL2V0cGNhcy5ha2FtYWkuY29tIiwiZXhwIjoxNTY5ODg4MDAwLCJzdWIiOiIzYTJiZDU2Zi1hYzc4LTRmZGEtYWZlMi1iZTliNjE4OGZiMmYiLCJpYXQiOjE1Njc1MTk5ODh9.Q6Lotp3AQCDC3mtzqlRZa_HiYkpN2GaIH2BApJrZgMPwsH8FsV5gkQrBwZSuehyGIstUhKN7JqrEUIjqOBGRzB2Rb8u8421IlpG4ffbBxjW2yt0t-3PkMGH3X8LnKQ6RYXXx11_UKUpfAEPxNeRCuKc4F0Q8977GBM77B8EbhUFjYV93f9RGUi_FcC0uIRM739s5hJHNWiKDj172S0wHIIPsEZwyC5UL2H5S1uYN_rEaMS3dHnRr3RxrIYzAIWe4ZoHLwxPSJUuI7LJRfBHWXPKdyOaUD7kj8NydteKIuaGYAtTzjUzf1sMSwHIPU3YHYwzvCpmx9lwcqWMGCI_mqQ\"',
            '-d',
            '{"akamai_device_id":"3a2bd56f-ac78-4fda-afe2-be9b6188fb2f", "tenant_id":"tenant-1", "mobile_device":false}',
            'https://signal-t-delta.dps.stage.akamai-access.com/device-posture/v1/user-signal-token'
        ],
        shell=True,
        stdout=subprocess.PIPE,
        #stderr=subprocess.PIPE
        )
    
    except subprocess.CalledProcessError as err:
        print('ERROR:', err)
    else:
        print('returncode:', completed.returncode)
        print('Have {} bytes in stdout: {!r}'.format(len(completed.stdout), completed.stdout.decode('utf-8')))
        # print('Have {} bytes in stderr: {!r}'.format(len(completed.stderr), completed.stderr.decode('utf-8')))


def run_multiple_times(n, callback):
    while n > 0:
        callback();
        n -= 1

def test_processpool_to_send_request():
    with pool(10) as p:
        run_multiple_times(1000)




if __name__ == '__main__':

    test_subprocess_basic()