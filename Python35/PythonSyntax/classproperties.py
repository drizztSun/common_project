
# <Properties>
class CProp:
    def __init__(self, x):
        # self.__x is a private member
        self.__x = x
        self._temp = 0

    # define property with property function
    def xgetter(self):
        print("CProp : get")
        return self.__x

    def xsetter(self, n):
        print("CProp : set")
        self.__x = n

    def xdeletor(self):
        print("CProp : del")
        del self.__x

    x = property(xgetter, xsetter, xdeletor, "It is x property")


    # Another way is @property

    @property
    def temperature(self):
        print("call temperature get function")
        return self._temp

    @temperature.setter
    def temperature(self, val):
        print("temperature set fucntion")
        self._temp = val

    @temperature.deleter
    def temperature(self):
        print("temperature delete function")
        del self._temp



if __name__ == "__main__":

    obj = CProp(5)

    print("x == {0}".format(obj.x))

    obj.x = 10

    print("x == {0}".format(obj.x))

    # del obj.x

    try:
        obj.x
    except (AttributeError, NameError) as error:
        print("catch a exception", error)


    print("Temperature = ", obj.temperature)

    print("Temperature = ", obj._temp)

    obj.temperature = 100

    print("Temperature = ", obj.temperature)

    print("Temperature = ", obj._temp)

    del obj.temperature

    try:
        obj.temperature
    except (AttributeError, NameError )as error:
        print("catch a exception", error)



    def test_signal_idp_username(self):
        tenants = self.generate_tenants(num_tenants=1, num_device_per_tenants=1)
        for tenant_id in tenants:
            uri = '/device-posture/v1/internal/configurations/{tenant_id}'.format(tenant_id=tenant_id)
            configs = {
                'blacklisted': False
            }
            res = self.client.post(uri,
                                   json.dumps(configs),
                                   content_type="application/json",
                                   HTTP_DEVICE_POSTURE_SERVICE_TOKEN=DPS['SERVICE_TOKEN'])
            self.assertEqual(201, res.status_code, res.content)

            for device_id in tenants[tenant_id]:
                signals = self.build_signal(tenant_id=tenant_id, device_id=device_id, idp_username='test_idp_username')
                uri = '/device-posture/v1/user-signal'
                res = self.client.post(uri,
                                       json.dumps(signals),
                                       content_type="application/json",
                                       HTTP_DEVICE_POSTURE_SERVICE_TOKEN=DPS['SERVICE_TOKEN'])
                self.assertEqual(202, res.status_code, res.content)

                device = Device.objects.get(tenant_id=tenant_id, device_id=device_id)
                self.assertEqual(device.signals['idp_username'], signals['idp_username'])
                self.assertEqual(1, DeviceHistory.objects.filter(device_id=device.id).count())

                for row in DeviceHistory.objects.filter(device_id=device.id):
                    print(row)
                    self.assertEqual(row.signals["idp_username"], "test_idp_username")


    def build_signal(self, tenant_id, device_id, mobile_device=False, cb_device_id="1", cs_aid='a', cs_cid='e5d4a79a091448bfb80afc724b3cf952', idp_username="default-idp-username"):
        return {
            "akamai_device_id": device_id,
            "tenant_id": tenant_id,
            "mobile_device": mobile_device,
            "machine_id": "564D7B63-81FF-7CAC-666C-4EADE0C17B30",
            "device_name": "btfs-mac-2.local",
            "user_id": "btfuser",
            "client_version": "0.1.1",
            "idp_username": idp_username,
            "os_name": "Mac OS X",

    def test_device_history_idp_username(self):
        uri = '/device-posture/v1/customers/%s/inventory/device-history/%s' % (TENANT_ID3, "devId1")
        res = self.client.get(uri, HTTP_DEVICE_POSTURE_SERVICE_TOKEN=DPS['SERVICE_TOKEN'])
        self.assertEqual(res.status_code, 200, res.content)
        history = res.json()['objects']
        print(history)
        self.assertEqual(1, len(history))
        self.assertEqual(TENANT_ID3 + '-devId3-username', history[0]["idp_username"])

