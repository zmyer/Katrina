//
// Created by xuanyin on 17/1/7.
//

#ifndef KATRINA_TEXTGENERATESPOUT_H
#define KATRINA_TEXTGENERATESPOUT_H

namespace Katrina {
    namespace spout {
        class TextGenerateSpout : public ISpout {
        public:
            ISpout *Clone() override {
                return new TextGenerateSpout(*this);
            }

            void Open(base::OutputCollector &outputCollector) override {
                _outputCollector = outputCollector;
            }

            void Close() override { }

            void Execute() override {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            base::Field DeclareFields() const override {
                return {"test"};
            }

        private:
            base::OutputCollector *_outputCollector;
        };
    }
}

#endif //KATRINA_TEXTGENERATESPOUT_H
