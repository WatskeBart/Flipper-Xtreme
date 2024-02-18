#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <furi_ble/profile_interface.h>
#include <core/common_defines.h>

#include <furi_hal_bt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RECORD_BT "bt"

typedef struct Bt Bt;

typedef enum {
    BtStatusUnavailable,
    BtStatusOff,
    BtStatusAdvertising,
    BtStatusConnected,
} BtStatus;

typedef void (*BtStatusChangedCallback)(BtStatus status, void* context);

/** Change BLE Profile
 * @note Call of this function leads to 2nd core restart
 *
 * @param bt                 Bt instance
 * @param profile_template   Profile template to change to
 * @param params             Profile parameters. Can be NULL
 *
 * @return          true on success
 */
FURI_WARN_UNUSED FuriHalBleProfileBase* bt_profile_start(
    Bt* bt,
    const FuriHalBleProfileTemplate* profile_template,
    FuriHalBleProfileParams params);

/** Stop current BLE Profile and restore default profile
 * @note Call of this function leads to 2nd core restart
 *
 * @param bt        Bt instance
 *
 * @return          true on success
 */
bool bt_profile_restore_default(Bt* bt);

/** Disconnect from Central
 *
 * @param bt        Bt instance
 */
void bt_disconnect(Bt* bt);

/** Set callback for Bluetooth status change notification
 *
 * @param bt        Bt instance
 * @param callback  BtStatusChangedCallback instance
 * @param context   pointer to context
 */
void bt_set_status_changed_callback(Bt* bt, BtStatusChangedCallback callback, void* context);

/** Forget bonded devices
 * @note Leads to wipe ble key storage and deleting bt.keys
 *
 * @param bt        Bt instance
 */
void bt_forget_bonded_devices(Bt* bt);

/** Set keys storage file path
 *
 * @param bt                    Bt instance
 * @param keys_storage_path     Path to file with saved keys
 */
void bt_keys_storage_set_storage_path(Bt* bt, const char* keys_storage_path);

/** Set default keys storage file path
 *
 * @param bt                    Bt instance
 */
void bt_keys_storage_set_default_path(Bt* bt);

// New methods

void bt_set_profile_adv_name(Bt* bt, const char* fmt, ...);

const char* bt_get_profile_adv_name(Bt* bt);

void bt_set_profile_mac_address(Bt* bt, const uint8_t mac[6]);

const uint8_t* bt_get_profile_mac_address(Bt* bt);

bool bt_remote_rssi(Bt* bt, uint8_t* rssi);

void bt_set_profile_pairing_method(Bt* bt, GapPairing pairing_method);
GapPairing bt_get_profile_pairing_method(Bt* bt);

/** Stop saving new peer key to flash (in .bt.keys file)
 * 
*/
void bt_disable_peer_key_update(Bt* bt);

/** Enable saving peer key to internal flash (enable by default)
 * 
 * @note This function should be called if bt_disable_peer_key_update was called before
*/
void bt_enable_peer_key_update(Bt* bt);

#ifdef __cplusplus
}
#endif
