//
// Created by StevensChew on 17/1/8.
//

#ifndef KATRINA_TRANSACTIONATTEMPT_H
#define KATRINA_TRANSACTIONATTEMPT_H

namespace Katrina {
    namespace bolt {
        class TransactionAttempt {
        public:
            TransactionAttempt(int transactionId, int attemptId) :
                    _transactionId(transactionId), _attemptId(attemptId) {

            }

            int GetTransactionId() const {
                return _transactionId;
            }

            int GetAttemptId() const {
                return _attemptId;
            }

        private:
            int _transactionId;
            int _attemptId;
        };
    }
}

#endif //KATRINA_TRANSACTIONATTEMPT_H
